#ifndef _CIA_H
#define _CIA_H

#include <random>
#include <algorithm>
#include <vector>

#include "CJoueur.h"
#include "CCarte.h"
#include "CPaquet.h"

using namespace std;

class Cia : public CJoueur
{
public:

	// CONSTRUCTEURS ET DESTRUCTEURS

	Cia(string sJOU_nomJoueur = "Joueur IA") : CJoueur(sJOU_nomJoueur) {};
	~Cia() {};

	// METHODES

	unique_ptr<CCarte> JOU_ChoixCarteAJouer();
};
#endif 

