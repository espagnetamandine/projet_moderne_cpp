#ifndef _CJEU_H
#define _CJEU_H

#include "CCarte.h"
#include "CPaquet.h"
#include "CJoueur.h"
#include <map>
#include <vector>

using namespace std;

template <class T>
class CJeu {
private:
	CPaquet pJEU_paquet_de_cartes;
	vector<CJoueur> vjJEU_joueurs;
	map<CJoueur, int> vjJEU_points;
	map<CJoueur, CCarte> mJEU_pli;
	unsigned int uiJEU_IdxJoueurCourrant;

public:
	CJeu();
	~CJeu();

	CPaquet JEU_GetPaquet() { return pJEU_paquet_de_cartes; }
	vector<CJoueur> JEU_GetJoueurs() { return vjJEU_joueurs; }
	map<CJoueur, int> JEU_GetPoints() { return vjJEU_points; }
	map<CJoueur, CCarte> JEU_GetPli() { return mJEU_pli; }

	bool JEU_FinDePartie();
	void JEU_LancementJeu(T type_jeu);
	void JEU_AfficherPoints();
	void JEU_AfficherGagnant();
};



#endif 