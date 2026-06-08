#ifndef _CPAQUETDecorateurAjouterJoker_H
#define _CPAQUETDecorateurAjouterJoker_H

#include "CPaquetDecorateur.h"

using namespace std;

class CPaquetDecorateurAjouterJoker : public CPaquetDecorateur {
public:
	CPaquetDecorateurAjouterJoker(unique_ptr<CPaquet> pPaquet) : CPaquetDecorateur(move(pPaquet))
	{
		PAQ_AjouterJoker();
	}

private:
	void PAQ_AjouterJoker()
	{
		vector<unique_ptr<CCarte>>& vcPaquet = getPAQ_cartes();
		vector<string>& vsCouleursGlobales = getPAQ_couleurs();

		unique_ptr<CCarte> pcNouvelleCarte1 = make_unique<CCarte>("Joker", 1);
		unique_ptr<CCarte> pcNouvelleCarte2 = make_unique<CCarte>("Joker", 1);

		vcPaquet.push_back(move(pcNouvelleCarte1));
		vcPaquet.push_back(move(pcNouvelleCarte2));

		vsCouleursGlobales.push_back("Joker");
	}
};

#endif 