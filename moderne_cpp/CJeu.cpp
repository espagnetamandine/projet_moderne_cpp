#include "CJeu.h"
#include "CJoueur.h"
#include "CRegle.h"
#include "CRegleDameDePique.h"
#include <iostream>

bool CJeu<CRegleDameDePique>::JEU_FinDePartie() {
	return false;
}


int CJeu<CRegleDameDePique>::JEU_ChagementDeJoueur() {
	//vector<CJoueur> joueurs = JEU_GetJoueurs();
	//if joueur courrant = joueurs.size() 
	return 0;
	//else return joueurs.get(idx_joueur_courrant++);
}


void CJeu<CRegleDameDePique>::JEU_LancementJeu(CRegleDameDePique type_jeu) {
	return;
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

