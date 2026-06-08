#ifndef _CPAQUETDecorateurTarot_H
#define _CPAQUETDecorateurTarot_H

#include "CPaquetDecorateur.h"

using namespace std;

class CPaquetDecorateurTarot : public CPaquetDecorateur {
public:
	CPaquetDecorateurTarot(unique_ptr<CPaquet> paquet) : CPaquetDecorateur(move(paquet))
	{
		PAQ_AjouterCartesDeTarot();
	}

private:
	void PAQ_AjouterCartesDeTarot()
	{
		unsigned int uiCarteValeur;

		vector<unique_ptr<CCarte>>& vcPaquet = getPAQ_cartes();
		vector<string>& vsCouleursGlobales = getPAQ_couleurs();

		vsCouleursGlobales.push_back("Atout");

		for (uiCarteValeur = 0; uiCarteValeur <= 21; uiCarteValeur++)
		{
			unique_ptr<CCarte> nouvelleCarte;

			if (uiCarteValeur == 0)
			{
				nouvelleCarte = make_unique<CCarte>("Atout", uiCarteValeur, "L'excuse");
			}
			else {
				nouvelleCarte = make_unique<CCarte>("Atout", uiCarteValeur);
			}

			vcPaquet.push_back(move(nouvelleCarte));
		}
	}
};

#endif 