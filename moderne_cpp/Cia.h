#ifndef _CIA_H
#define _CIA_H

#include "CJoueur.h"
#include "CCarte.h"
#include "CPaquet.h"

using namespace std;

class Cia : public CJoueur
{
public:
	Cia(string sJOU_nomJoueur = "Joueur IA") : CJoueur(sJOU_nomJoueur) {};
	~Cia();

	unique_ptr<CCarte> JOU_ChoixCarteAJouer();
};
#endif 

