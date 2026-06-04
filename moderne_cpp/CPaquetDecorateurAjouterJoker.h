#ifndef _CPAQUETDecorateurAjouterJoker_H
#define _CPAQUETDecorateurAjouterJoker_H

#include "CPaquetDecorateur.h"

using namespace std;

class CPaquetDecorateurAjouterJoker : public CPaquetDecorateur {
public:
	CPaquetDecorateurAjouterJoker(unique_ptr<CPaquet> paquet) : CPaquetDecorateur(move(paquet))
	{
		PAQ_AjouterJoker();
	}

private:
	void PAQ_AjouterJoker()
	{
		vector<CCarte>& vcPaquet = getPAQ_cartes();
		vector<string>& vsCouleursGlobales = getPAQ_couleurs();

		vcPaquet.push_back(CCarte("Joker", 0));
		vcPaquet.push_back(CCarte("Joker", 0));

		vsCouleursGlobales.push_back("Joker");
	}
};

#endif 