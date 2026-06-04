#ifndef _CHUMAIN_H
#define _CHUMAIN_H
#include "CJoueur.h"
#include "CCarte.h"
#include <string>

class CHumain : public CJoueur
{
public:
	CHumain(std::string sNom, int iEquipe);
	CCarte HUMAIN_Choix_Carte_A_Jouer();

};
#endif 