#ifndef _CHUMAIN_H
#define _CHUMAIN_H
#include "CJoueur.h"
#include "CCarte.h"

class CHumain : public CJoueur
{
public:
	CHumain();
	CHumain(std::string sNom, int iEquipe);
	CCarte JOUEUR_Choix_Carte_A_Jouer();
	~CHumain();
};
#endif 