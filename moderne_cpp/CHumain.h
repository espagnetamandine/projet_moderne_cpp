#ifndef _CHUMAIN_H
#define _CHUMAIN_H

#include "CJoueur.h"

#include <vector>
#include <iostream>

using namespace std;

class CHumain : public CJoueur
{
public:

	// CONSTRUCTEURS ET DESTRUCTEURS

	CHumain(string sJOU_nomJoueur = "Joueur humain") : CJoueur(sJOU_nomJoueur) {};
	~CHumain() {};

	// METHODES

	virtual unsigned int JOU_ChoixCarteAJouer();
};
#endif 