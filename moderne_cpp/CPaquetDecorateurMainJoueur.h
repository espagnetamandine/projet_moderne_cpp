#ifndef _CPAQUETDecorateurMainJoueur_H
#define _CPAQUETDecorateurMainJoueur_H

#include "CPaquetDecorateur.h"

using namespace std;

class CPaquetDecorateurMainJoueur : public CPaquetDecorateur {
public:

	// CONSTRUCTEURS ET DESTRUCTEURS

	CPaquetDecorateurMainJoueur(unique_ptr<CPaquet> pPaquet) : CPaquetDecorateur(move(pPaquet)) {};
};

#endif 