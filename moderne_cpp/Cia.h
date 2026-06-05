#ifndef _CIA_H
#define _CIA_H

#include "CJoueur.h"
#include "CCarte.h"
#include "CPaquet.h"
#include <string>

class Cia : public CJoueur
{
public:
	Cia();
	Cia(std::string sNom, int iEquipe);
	CCarte JOUEUR_Choix_Carte_A_Jouer();
	~Cia();
};
#endif 

