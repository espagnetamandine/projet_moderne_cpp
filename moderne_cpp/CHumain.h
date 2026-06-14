#ifndef _CHUMAIN_H
#define _CHUMAIN_H

#include <vector>
#include <iostream>

#include "CJoueur.h"
#include "CCarte.h"

using namespace std;

class CHumain : public CJoueur
{
public:

	// CONSTRUCTEURS ET DESTRUCTEURS

	CHumain(string sJOU_nomJoueur = "Joueur humain") : CJoueur(sJOU_nomJoueur) {};
	~CHumain() {};

	// METHODES

	unique_ptr<CCarte> JOU_ChoixCarteAJouer();
};
#endif 