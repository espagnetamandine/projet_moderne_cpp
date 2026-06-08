
#ifndef _CJEU_H
#define _CJEU_H

#include "CRegle.h"
#include "CCarte.h"
#include "CPaquet.h"
#include "CJoueur.h"
#include "CEquipe.h"

#include <map>
#include <vector>

using namespace std;

class CJeu {
private:
	// unique ptr car CRegle et cJoueur sont virtuelles pures, à vérifier si c bien ça + adapter les methodes
	unique_ptr<CRegle> strategieRegle; 
	unique_ptr<CJoueur> strategieJoueur;

	unique_ptr<CPaquet> pJEU_paquet_de_cartes; // CPaquet classe interface donc unique_ptr
	vector<CJoueur> vjJEU_joueurs;
	unsigned int uiJEU_IdxJoueurCourrant;
	map<CEquipe, int> vjJEU_points;
	map<CJoueur, CCarte> mJEU_pli;

public:
	CJeu();

	void JEU_setStrategieRegle(unique_ptr<CRegle> regle) { strategieRegle = move(regle); }
	void JEU_setStrategieJoueur(unique_ptr<CJoueur> joueur) { strategieJoueur = move(joueur); }

	//void JEU_AjouterJoueur() { strategieJoueur.CJoueur(); }
	void JEU_JouerPartie(); 
};
#endif 