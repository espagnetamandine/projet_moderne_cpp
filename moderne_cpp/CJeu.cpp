#include "CJeu.h"
#include "CRegleManager.h"
#include "CJoueur.h"
#include "CPaquet.h"
#include "CEquipe.h"

#include <iostream>
#include <cstdlib>

/********************************************************/
/*             CONSTRUCTEURS ET DESTRUCTEURS            */
/********************************************************/

CJeu::CJeu(string sNom) {
	sJEU_nom = sNom;
	prJEU_strategieRegle = CRegleManager::REG_CreerRegle(sNom);

	pJEU_paquetDeCartes = CPaquetManager::PAQ_CreerPaquet(sNom);
	pJEU_defausse = CPaquetManager::PAQ_CreerPaquet("Main du joueur");
	pJEU_pli = CPaquetManager::PAQ_CreerPaquet("Main du joueur");
	
	uiJEU_IdJoueurCourrant = 0;
}
CJeu::~CJeu() = default;

/********************************************************/
/*                  GETTER ET SETTER                    */
/********************************************************/

string CJeu::JEU_GetNomJoueur(unsigned int uiIdJoueur) {
	return vjJEU_joueurs[uiIdJoueur]->JOU_GetNomJoueur();
}

bool CJeu::JEU_SetNombreJoueur(unsigned int uiNbJoueurs) {
	return prJEU_strategieRegle->REG_VerificationNbJoueur(uiNbJoueurs);
}

/********************************************************/
/*                METHODE PRINCIPALE                    */
/********************************************************/

void CJeu::JEU_JouerPartie() {
	unique_ptr<CCarte> carte;
	unsigned int uiIndiceJoueurGagnant = 100;
	unsigned int uiPremierJoueurManche = 0;

	prJEU_strategieRegle->REG_DebutPartie(pJEU_paquetDeCartes, vjJEU_joueurs, mJEU_points);
	while (!prJEU_strategieRegle->REG_ConditionFinPartie(mJEU_points)) // partie
	{
		// debut manche
		unsigned int uiIndicePremierJoueur = prJEU_strategieRegle->REG_DebutManche(pJEU_paquetDeCartes, vjJEU_joueurs, mJEU_points, uiPremierJoueurManche);
		uiJEU_IdJoueurCourrant = uiIndicePremierJoueur;
		uiPremierJoueurManche = uiIndicePremierJoueur;

		// C'est bien ce joueur qui commence le premier pli de cette manche
		uiJEU_IdJoueurCourrant = uiIndicePremierJoueur;

		while (!prJEU_strategieRegle->REG_ConditionFinManche(vjJEU_joueurs)) // manche
		{
			// réinitialiser le pli
			vuJEU_idJoueurPli.clear();
			pJEU_pli->PAQ_GetCartes().clear();

			while (pJEU_pli->PAQ_GetCartes().size() != vjJEU_joueurs.size()) // pli 
			{
				// Affichage de la main du joueur avec le pli pour qu'il puisse choisir sa carte
				if (!vjJEU_joueurs[uiJEU_IdJoueurCourrant]->JOU_EstIa())
				{
					unsigned int uiNumEquipe = 0;
					int iScoreEquipe = 0;

					map<unique_ptr<CEquipe>, int>::iterator it;

					for (it = mJEU_points.begin(); it != mJEU_points.end(); ++it) {
					
						vector<unsigned int> vNumeros = it->first->getEQU_equipe();

						for (unsigned int uiBoucle = 0; uiBoucle < vNumeros.size(); ++uiBoucle) {
							if (vNumeros[uiBoucle] == uiJEU_IdJoueurCourrant) {
								uiNumEquipe = it->first->getEQU_numeroEquipe();
								iScoreEquipe = it->second;
								break;
							}
						}
					}

					CConsole::COS_AfficherEcranSecretJoueur(vjJEU_joueurs[uiJEU_IdJoueurCourrant], uiNumEquipe, iScoreEquipe);

					JEU_AfficherPli();
					cout << endl;
				}

				bool bCarteValidee = false;

				while (!bCarteValidee)
				{
					vector<unique_ptr<CCarte>>& upJOU_mainJoueur = vjJEU_joueurs[uiJEU_IdJoueurCourrant]->JOU_GetMain()->PAQ_GetCartes();

					unsigned int uiIndexCarteChoisie = vjJEU_joueurs[uiJEU_IdJoueurCourrant]->JOU_ChoixCarteAJouer();

					if (!prJEU_strategieRegle->REG_CarteValide(*(upJOU_mainJoueur[uiIndexCarteChoisie]), vjJEU_joueurs[uiJEU_IdJoueurCourrant]->JOU_GetMain(), pJEU_pli, vuJEU_idJoueurPli))
					{
						cout << "\nVeuillez resaisir.\n" << endl;
					}
					else
					{
						carte = move(upJOU_mainJoueur[uiIndexCarteChoisie]);

						vector<unique_ptr<CCarte>>::iterator it = upJOU_mainJoueur.begin() + uiIndexCarteChoisie;
						upJOU_mainJoueur.erase(it);

						pJEU_pli->PAQ_AjouterCarte(move(carte));
						vuJEU_idJoueurPli.push_back(uiJEU_IdJoueurCourrant);

						uiJEU_IdJoueurCourrant = (uiJEU_IdJoueurCourrant + 1) % vjJEU_joueurs.size();
						bCarteValidee = true;
					}
				}
			}

			CConsole::COS_NettoyerEcran();

			uiIndiceJoueurGagnant = prJEU_strategieRegle->REG_DeterminerIndiceGagnantPli(pJEU_pli, vuJEU_idJoueurPli);
			prJEU_strategieRegle->REG_AfficherGagnantPli(vjJEU_joueurs, uiIndiceJoueurGagnant);
			JEU_AfficherPli();
			uiJEU_IdJoueurCourrant = uiIndiceJoueurGagnant;

			prJEU_strategieRegle->REG_CalculerPointsPli(pJEU_pli, uiIndiceJoueurGagnant, mJEU_points, pJEU_defausse);
			vuJEU_idJoueurPli.clear();
			while (!pJEU_pli->PAQ_GetCartes().empty()) {
				pJEU_pli->PAQ_GetCartes().pop_back();
			}

			cout << "\nAppuyez sur ENTREE pour passer au pli suivant...";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();

			CConsole::COS_NettoyerEcran();
		}
		prJEU_strategieRegle->REG_CalculerPointsManche(pJEU_pli, uiIndiceJoueurGagnant, mJEU_points, pJEU_defausse, vjJEU_joueurs);

		if (pJEU_defausse != nullptr) {
			vector<unique_ptr<CCarte>>& cartesDefausse = pJEU_defausse->PAQ_GetCartes();
			while (!cartesDefausse.empty()) {
				pJEU_paquetDeCartes->PAQ_AjouterCarte(move(cartesDefausse.back()));
				cartesDefausse.pop_back();
			}
		}

		uiPremierJoueurManche = (uiPremierJoueurManche + 1) % vjJEU_joueurs.size();
	}
	prJEU_strategieRegle->REG_AfficherGagnantPartie(mJEU_points, vjJEU_joueurs);
}

void CJeu::JEU_SetStrategieRegle(unique_ptr<CRegle> regle) {
	prJEU_strategieRegle = move(regle);
}

/********************************************************/
/*                     AFFICHAGE                        */
/********************************************************/

void CJeu::JEU_AfficherPoints() {
	prJEU_strategieRegle->REG_AfficherPoints(mJEU_points);
}

void CJeu::JEU_AfficherEquipe() {
	for (auto it = mJEU_points.begin(); it != mJEU_points.end(); ++it)
	{
		vector<unsigned int> numerosJoueurs = it->first->getEQU_equipe();
		for (unsigned int numeroJoueur : numerosJoueurs) {
			cout << vjJEU_joueurs[numeroJoueur]->JOU_GetNomJoueur() << endl;
		}
	}
}

void CJeu::JEU_AfficherPli() {
	cout << "\nTapis de jeu :" << endl;

	vector<unique_ptr<CCarte>>& cartesDuPli = pJEU_pli->PAQ_GetCartes();
	
	if (cartesDuPli.empty()) {
		cout << "Le pli est vide" << endl;
	}
	else {
		for (size_t i = 0; i < cartesDuPli.size(); i++) {
			unsigned int idJoueur = vuJEU_idJoueurPli[i];
			cout << " -> " << vjJEU_joueurs[idJoueur]->JOU_GetNomJoueur() << " a joue : " << *(cartesDuPli[i]) << endl;
		}
	}
}