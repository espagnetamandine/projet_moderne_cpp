#ifndef _CIA_H
#define _CIA_H

#include "CJoueur.h"
#include "CCarte.h"
#include <string>

class Cia : public CJoueur
{
public:
	Cia(std::string sNom, int iEquipe);
	CCarte IA_Choix_Carte_A_Jouer();
};
#endif 

