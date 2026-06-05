#ifndef _CPAQUETDecorateurMainJoueur_H
#define _CPAQUETDecorateurMainJoueur_H

#include "CPaquetDecorateur.h"

using namespace std;

class CPaquetDecorateurMainJoueur : public CPaquetDecorateur {
public:
	CPaquetDecorateurMainJoueur(unique_ptr<CPaquet> paquet) : CPaquetDecorateur(move(paquet)) {};
};

#endif 