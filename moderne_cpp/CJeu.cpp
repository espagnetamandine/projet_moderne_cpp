
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
			
			while (uiJEU_IdJoueurCourrant != vjJEU_joueurs.size()) // pli 
			{
				carte = vjJEU_joueurs[uiJEU_IdJoueurCourrant]->JOU_choixCarteAJouer();

				if (!prJEU_strategieRegle->REG_CarteValide(*carte)) { } //erreur 
				else
				{
					pJEU_pli->PAQ_AjouterCarte(move(carte));
					vuJEU_idJoueurPli.push_back(uiJEU_IdJoueurCourrant);
					uiJEU_IdJoueurCourrant++;
				}
			}
			uiIndiceJoueurGagnant = prJEU_strategieRegle->REG_DeterminerIndiceGagnantPli(pJEU_pli, vuJEU_idJoueurPli);
			prJEU_strategieRegle->REG_AfficherGagnantPli(uiIndiceJoueurGagnant);
		}
	}
	prJEU_strategieRegle->REG_AfficherGagnantPartie();
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