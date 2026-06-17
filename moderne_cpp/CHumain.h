#ifndef _CHUMAIN_H
#define _CHUMAIN_H

#include "CJoueur.h"

#include <vector>
#include <iostream>

using namespace std;

class CHumain : public CJoueur
{
public:

	// Constructeurs et destructeurs

	CHumain(string sJOU_nomJoueur = "Joueur humain") : CJoueur(sJOU_nomJoueur) {};
	~CHumain() {};

	// Méthodes

	virtual unsigned int JOU_ChoixCarteAJouer();
};
#endif 