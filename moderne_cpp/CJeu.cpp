
#include "CJeu.h"
#include "CRegleDameDePique.h"
#include <iostream>

CJeu::CJeu(const string& sTypeJeu) {
	if(sTypeJeu == "Dame de pique")
}


void CJeu::JEU_JouerPartie() {
	unique_ptr<CCarte> carte;
	strategieRegle->REG_DistribuerCartes(vjJEU_joueurs, move(pJEU_paquet_de_cartes));
	while (!strategieRegle->REG_FinDePartie()) // partie
	{
		while (!strategieRegle->REG_FinDeManche()) // manche
		{
			while (uiJEU_IdxJoueurCourrant != vjJEU_joueurs.size()) // pli 
			{
				carte = vjJEU_joueurs[uiJEU_IdxJoueurCourrant]->JOUEUR_Choix_Carte_A_Jouer();

				if (uiJEU_IdxJoueurCourrant == 0 && !strategieRegle->REG_PremiereCarte(*carte)) { /* erreur*/ }

				else if (!strategieRegle->REG_CarteValide(*carte)) { /*erreur*/ }

				else
				{
					unique_ptr<CCarte> pCarte = move(carte);
					mJEU_pli[vjJEU_joueurs[uiJEU_IdxJoueurCourrant].get()] = move(carte);
					strategieRegle->REG_GagnePli(); //calcule les points 
				}
			}
		}
		strategieRegle->REG_AfficherPoints(); // points de la manche 
	}
	strategieRegle->REG_AfficherPoints(); // points de la partie
	strategieRegle->REG_AfficherGagnant();
}