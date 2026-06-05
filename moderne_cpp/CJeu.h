#ifndef _CJEU_H
#define _CJEU_H

#include "CRegle.h"
#include "CCarte.h"
#include "CPaquet.h"
#include "CJoueur.h"
#include <map>
#include <vector>

using namespace std;

class CJeu {
private:
	// unique ptr car CRegle et cJoueur sont virtuelles pures, à vérifier si c bien ça + adapter les methodes
	unique_ptr<CRegle> strategieRegle; 
	unique_ptr<CJoueur> strategieJoueur;

public:
	CJeu();

	//void JEU_setStrategieRegle(CRegle regle) { strategieRegle = regle; }
	// void JEU_setStrategieJoueur(CJoueur joueur) { strategieJoueur = joueur; }

	// void JEU_AjouterJoueur() { strategieJoueur.CJoueur(); }
	// void JEU_LancerPartie() { strategieRegle.REG_JouerPartie(); }
};



#endif 