
#include "CJeu.h"
#include "CRegleDameDePique.h"
#include "CPaquetManager.h"
#include "CRegleManager.h"
#include <iostream>

CJeu::CJeu(string sNom) {
	sJEU_nom = sNom;
	prJEU_strategieRegle = CRegleManager::REG_CreerRegle(sNom);

	pJEU_paquetDeCartes = CPaquetManager::PAQ_CreerPaquet(sNom);
	pJEU_defausse = CPaquetManager::PAQ_CreerPaquet("Main du joueur");
	pJEU_pli = CPaquetManager::PAQ_CreerPaquet("Main du joueur");
	
	uiJEU_IdJoueurCourrant = 0;
	uiJEU_compteurManche = 0;
	uiJEU_compteurPli = 0;
}


void CJeu::JEU_JouerPartie() {
	unique_ptr<CCarte> carte;
	unsigned int uiIndiceJoueurGagnant = 100; // grande valeur car pas -1

	prJEU_strategieRegle->REG_DebutPartie();
	while (!prJEU_strategieRegle->REG_ConditionFinPartie()) // partie
	{
		prJEU_strategieRegle->REG_DebutManche();
		while (!prJEU_strategieRegle->REG_ConditionFinManche()) // manche
		{
			//
			uiJEU_IdJoueurCourrant = 0;
			vuJEU_idJoueurPli.clear();
			pJEU_pli->PAQ_GetCartes().clear();
			//
			while (uiJEU_IdJoueurCourrant != vjJEU_joueurs.size()) // pli 
			{
				carte = vjJEU_joueurs[uiJEU_IdJoueurCourrant]->JOU_ChoixCarteAJouer();

				if (!prJEU_strategieRegle->REG_CarteValide(*carte)) { } //erreur 
				else
				{
					pJEU_pli->PAQ_AjouterCarte(move(carte));
					vuJEU_idJoueurPli.push_back(uiJEU_IdJoueurCourrant);
					uiJEU_IdJoueurCourrant++;
				}
			}
			uiIndiceJoueurGagnant = prJEU_strategieRegle->REG_DeterminerIndiceGagnantPli(pJEU_pli, vuJEU_idJoueurPli);
			prJEU_strategieRegle->REG_AfficherGagnantPli(vjJEU_joueurs, uiIndiceJoueurGagnant);
			prJEU_strategieRegle->REG_CalculerPointsPli();
		}
		prJEU_strategieRegle->REG_CalculerPointsManche();
	}
	prJEU_strategieRegle->REG_AfficherGagnantPartie(vjJEU_joueurs, uiIndiceJoueurGagnant);
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


//pas fini, ne fonctionne pas pour le moment 
void CJeu::JEU_AfficherPli() {             
	//auto& cartesDuPli = pJEU_pli->getPAQ_Cartes();
	vector<unique_ptr<CCarte>>& cartesDuPli = pJEU_pli->PAQ_GetCartes();
	for (unsigned int i = 0; i < vuJEU_idJoueurPli.size(); i++) {
		//cout << vjJEU_joueurs[i].get()->getJOU_nomJoueur() << " : " << *(cartesDuPli[i]);
	}
	//pJEU_pli->PAQ_Afficher();
}

// appelle à afficher main joueur de regle car ça affiche la main, le nom du joueur, le pli et les equipes l'interface peut changer en fonction des jeux
void CJeu::JEU_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur) {
	prJEU_strategieRegle->REG_AfficherMainJoueur(pJoueur);
}





//void CJeu::JEU_JouerPartie() {
//	unique_ptr<CCarte> carte;
//	prJEU_strategieRegle->REG_DistribuerCartes(vjJEU_joueurs, move(ppJEU_paquetDeCartes));
//	while (!prJEU_strategieRegle->REG_FinDePartie()) // partie
//	{
//		while (!prJEU_strategieRegle->REG_FinDeManche()) // manche
//		{
//			while (uiJEU_IdxJoueurCourrant != vjJEU_joueurs.size()) // pli 
//			{
//				carte = vjJEU_joueurs[uiJEU_IdxJoueurCourrant]->JOUEUR_Choix_Carte_A_Jouer();
//
//				if (uiJEU_IdxJoueurCourrant == 0 && !prJEU_strategieRegle->REG_PremiereCarte(*carte)) { /* erreur*/ }
//
//				else if (!prJEU_strategieRegle->REG_CarteValide(*carte)) { /*erreur*/ }
//
//				else
//				{
//					mJEU_pli[vjJEU_joueurs[uiJEU_IdxJoueurCourrant].get()] = move(carte);
//					prJEU_strategieRegle->REG_GagnePli(mJEU_pli); //calcule les points 
//				}
//			}
//		}
//		prJEU_strategieRegle->REG_AfficherPoints(); // points de la manche 
//	}
//	prJEU_strategieRegle->REG_AfficherPoints(); // points de la partie
//	prJEU_strategieRegle->REG_AfficherGagnant();
//}