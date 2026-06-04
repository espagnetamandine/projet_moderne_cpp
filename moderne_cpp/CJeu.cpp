#include "CJeu.h"
#include "CJoueur.h"
#include "CRegle.h"
#include "CRegleDameDePique.h"
#include <iostream>

CJeu::CJeu() {
	pJEU_paquet_de_cartes = new CPaquet();
	vjJEU_joueurs = new vector<CJoueur>;
	vjJEU_points = new map<CJoueur, int>;
	mJEU_pli = map<CJoueur, CCarte>;
	uiJEU_IdxJoueurCourrant = 0;
}


bool CJeu<CRegleDameDePique>::JEU_FinDePartie() {
	return REG_FinDePartie();
}


void CJeu<CRegleDameDePique>::JEU_LancementJeu(CRegleDameDePique type_jeu) {
	Carte carte = new Carte();
	
	REG_DistribuerCartes();
	while (!JEU_FinDePartie()) // partie
	{
		while (!REG_FinDeManche()) // manche
		{
			while (uiJEU_IdxJoueurCourrant != vjJEU_joueurs.size()) // pli 
			{
				carte = JEU_ChoixCarte();

				if (uiJEU_IdxJoueurCourrant == 0 && !REG_PremiereCarte()) { /* erreur*/ }

				else if (!REG_CarteValide(carte)) { /*erreur*/ }

				else
				{
					mJEU_pli[uiJEU_IdxJoueurCourrant] = carte;
					REG_GagnePli(); //calcule les points 
				}
			}
		}
		JEU_AfficherPoints(); // points de la manche 
	}
	JEU_AfficherPoints(); // points de la partie
	JEU_AfficherGagnant();
}

bool EstDansVecteur(vector<int> v, int numero) {
	for (int i : v) {
		if (numero == i)
			return true;
	}
	return false;
}

void CJeu<CRegleDameDePique>::JEU_AfficherPoints() {
	vector<int> numeros;
	for (int i = 0; i < vjJEU_joueurs.size(); i++) {
		int numero_equipe_j = vjJEU_joueurs.JOU_GetEquipe();
		if(EstDansVecteur(numeros, numero_equipe_j)) {
			numeros.push_back(numero_equipe_j);
			cout << "Equipe " << numero_equipe_j << " : " << vjJEU_joueurs[i] << endl;
		}
	}
}



void CJeu<CRegleDameDePique>::JEU_AfficherGagnant() {
	CJoueur jJoueurMax = vjJEU_joueurs[0];
	int iPointsMax = 0;
	for (auto it = vjJEU_points.begin(); it != vjJEU_points.end(); ++it)
	{
		if (it->second > iPointsMax)
		{
			iPointsMax = it->second;
			jJoueurMax = it->first;
		}
	}
	cout << "L'équipe gagnant est : " << jJoueuMax.JOU_GetEquipe() << " avec " << iPointsMax << " Points." << endl;
	
	cout << "Félicitation ";
	for (CJoueur j : vjJEU_joueurs)
	{
		if (j.JOU_GetEquipe() == jJoueurMax.JOU_GetEquipe)
		{
			cout << j.JOU_GetName();
		}
	}
	cout << endl;
}

