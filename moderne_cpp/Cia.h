#ifndef _CIA_H
#define _CIA_H

#include "CJoueur.h"

#include <random>
#include <algorithm>
#include <vector>

using namespace std;

class Cia : public CJoueur
{
public:

	// CONSTRUCTEURS ET DESTRUCTEURS

	Cia(string sJOU_nomJoueur = "Joueur IA") : CJoueur(sJOU_nomJoueur) {};
	~Cia() {};

	// METHODES

	unique_ptr<CCarte> JOU_ChoixCarteAJouer();
	virtual bool JOU_EstIa() const { return true; }
};
#endif 

