#include "CJeu.h"
#include "CRegleManager.h"
#include "CJoueur.h"
#include "CPaquet.h"
#include "CEquipe.h"

#include <iostream>
#include <cstdlib>

CJeu::CJeu(string sNom) {
	sJEU_nom = sNom;
	prJEU_strategieRegle = CRegleManager::REG_CreerRegle(sNom);

	pJEU_paquetDeCartes = CPaquetManager::PAQ_CreerPaquet(sNom);
	pJEU_defausse = CPaquetManager::PAQ_CreerPaquet("Main du joueur");
	pJEU_pli = CPaquetManager::PAQ_CreerPaquet("Main du joueur");
	
	uiJEU_IdJoueurCourrant = 0;
}
CJeu::~CJeu() = default;

string CJeu::JEU_GetNomJoueur(unsigned int uiIdJoueur) {
	return vjJEU_joueurs[uiIdJoueur]->JOU_GetNomJoueur();
}

bool CJeu::JEU_SetNombreJoueur(unsigned int uiNbJoueurs) {
	return prJEU_strategieRegle->REG_SetNbJoueur(uiNbJoueurs);
}

void CJeu::JEU_JouerPartie() {
	unique_ptr<CCarte> carte;
	unsigned int uiIndiceJoueurGagnant = 100; // grande valeur car pas -1 (unsigned int) mais doit être different des numeros de joueurs 

	prJEU_strategieRegle->REG_DebutPartie(pJEU_paquetDeCartes, vjJEU_joueurs, mJEU_points);
	while (!prJEU_strategieRegle->REG_ConditionFinPartie(mJEU_points)) // partie
	{
		// debut manche
		unsigned int uiIndicePremierJoueur = prJEU_strategieRegle->REG_DebutManche(pJEU_paquetDeCartes, vjJEU_joueurs, mJEU_points, uiJEU_IdJoueurCourrant);
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

				carte = vjJEU_joueurs[uiJEU_IdJoueurCourrant]->JOU_ChoixCarteAJouer();

				bool bCarteValidee = false;
				while (!bCarteValidee)
				{
					if (!prJEU_strategieRegle->REG_CarteValide(*carte, vjJEU_joueurs[uiJEU_IdJoueurCourrant]->JOU_GetMain()))
					{
						cout << "\nCarte invalide !\n" << endl;
						vjJEU_joueurs[uiJEU_IdJoueurCourrant]->JOU_GetMain()->PAQ_AjouterCarte(move(carte));
					}
					else
					{
						bCarteValidee = true;
						pJEU_pli->PAQ_AjouterCarte(move(carte));
						vuJEU_idJoueurPli.push_back(uiJEU_IdJoueurCourrant);
						uiJEU_IdJoueurCourrant = (uiJEU_IdJoueurCourrant + 1) % vjJEU_joueurs.size();
					}
				}
			}

			uiIndiceJoueurGagnant = prJEU_strategieRegle->REG_DeterminerIndiceGagnantPli(pJEU_pli, vuJEU_idJoueurPli);
			prJEU_strategieRegle->REG_AfficherGagnantPli(vjJEU_joueurs, uiIndiceJoueurGagnant);
		}
		prJEU_strategieRegle->REG_CalculerPointsManche();
	}
	prJEU_strategieRegle->REG_AfficherGagnantPartie(mJEU_points, vjJEU_joueurs);
}

void CJeu::JEU_SetStrategieRegle(unique_ptr<CRegle> regle) {
	prJEU_strategieRegle = move(regle);
}

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

// appelle à afficher main joueur de regle car ça affiche la main, le nom du joueur, le pli et les equipes l'interface peut changer en fonction des jeux
void CJeu::JEU_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur) {
	prJEU_strategieRegle->REG_AfficherMainJoueur(pJoueur);
}