#ifndef _CHUMAIN_H
#define _CHUMAIN_H
#include "CJoueur.h"
#include "CCarte.h"

using namespace std;

class CHumain : public CJoueur
{
public:
	CHumain();
	CHumain(string sJOU_nomJoueur);
	unique_ptr<CCarte> JOU_choixCarteAJouer();
	~CHumain();
};
#endif 