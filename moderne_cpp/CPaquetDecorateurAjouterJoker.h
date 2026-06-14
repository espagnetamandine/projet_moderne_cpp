#ifndef _CPAQUETDecorateurAjouterJoker_H
#define _CPAQUETDecorateurAjouterJoker_H

#include "CPaquetDecorateur.h"

using namespace std;

class CPaquetDecorateurAjouterJoker : public CPaquetDecorateur {
public:

	// CONSTRUCTEURS ET DESTRUCTEURS

	CPaquetDecorateurAjouterJoker(unique_ptr<CPaquet> pPaquet) : CPaquetDecorateur(move(pPaquet))
	{
		PAQ_AjouterJoker();
	}

private:

	// METHODES

	void PAQ_AjouterJoker()
	{
		vector<unique_ptr<CCarte>>& vcPaquet = PAQ_GetCartes();
		vector<string>& vsCouleursGlobales = PAQ_GetCouleurs();

		unique_ptr<CCarte> pcNouvelleCarte1 = make_unique<CCarte>("Joker", 1);
		unique_ptr<CCarte> pcNouvelleCarte2 = make_unique<CCarte>("Joker", 1);

		vcPaquet.push_back(move(pcNouvelleCarte1));
		vcPaquet.push_back(move(pcNouvelleCarte2));

		vsCouleursGlobales.push_back("Joker");
	}
};

#endif 