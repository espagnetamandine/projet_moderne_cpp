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
	unique_ptr<CRegle> strategieRegle; // unique pointeur a verifier : il faut modifier le set 
	CJoueur strategieJoueur;

public:
	CJeu();
	~CJeu();

	//void JEU_setStrategieRegle(CRegle regle) { strategieRegle = regle; }
	void JEU_setStrategieJoueur(CJoueur joueur) { strategieJoueur = joueur; }

	void JEU_AjouterJoueur();
	void JEU_LancerPartie(); 
};



#endif 