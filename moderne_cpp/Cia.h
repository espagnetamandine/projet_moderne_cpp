#ifndef _CIA_H
#define _CIA_H

#include "CJoueur.h"
#include "CCarte.h"
#include "CPaquet.h"



using namespace std;

class Cia : public CJoueur
{
public:
	Cia();
	Cia(string sNom);
	CCarte JOUEUR_Choix_Carte_A_Jouer();
	~Cia();
};
#endif 

