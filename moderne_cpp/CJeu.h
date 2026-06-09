
#ifndef _CJEU_H
#define _CJEU_H

#include "CRegle.h"
#include "CCarte.h"
#include "CPaquet.h"
#include "CJoueur.h"
#include "CEquipe.h"

#include <vector>
#include <map>

using namespace std;

class CJeu {
private:
	unique_ptr<CRegle> strategieRegle;

	unique_ptr<CPaquet> pJEU_paquet_de_cartes;
	vector<unique_ptr<CJoueur>> vjJEU_joueurs;
	unsigned int uiJEU_IdxJoueurCourrant;
	map<CEquipe, int> vjJEU_points;
	map<CJoueur*, unique_ptr<CCarte>> mJEU_pli;

public:
	CJeu(const string& sTypeJeu);

	void JEU_setStrategieRegle(unique_ptr<CRegle> regle) { strategieRegle = move(regle); }
	void JEU_AjouterJoueur(unique_ptr<CJoueur> joueur) { vjJEU_joueurs.push_back(move(joueur)); }
	void JEU_JouerPartie(); 
};
#endif 