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
	Cia(string sJOU_nomJoueur);
	unique_ptr<CCarte> JOU_choixCarteAJouer();
	~Cia();
};
#endif 

