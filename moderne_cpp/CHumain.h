#ifndef _CHUMAIN_H
#define _CHUMAIN_H
#include "CJoueur.h"
#include "CCarte.h"

using namespace std;

class CHumain : public CJoueur
{
public:
	CHumain();
	CHumain(string sNom);
	CCarte JOUEUR_Choix_Carte_A_Jouer();
	~CHumain();
};
#endif 