#ifndef _CPAQUETDecorateurTarot_H
#define _CPAQUETDecorateurTarot_H

#include "CPaquetDecorateur.h"

using namespace std;

class CPaquetDecorateurTarot : public CPaquetDecorateur {
public:

	// Constructeurs et destructeurs

	CPaquetDecorateurTarot(unique_ptr<CPaquet> pPaquet) : CPaquetDecorateur(move(pPaquet))
	{
		PAQ_AjouterCartesDeTarot();
	}

private:

	// Méthodes

	void PAQ_AjouterCartesDeTarot()
	{
		unsigned int uiCarteValeur;

		vector<unique_ptr<CCarte>>& vcPaquet = PAQ_GetCartes();
		vector<string>& vsCouleursGlobales = PAQ_GetCouleurs();

		vsCouleursGlobales.push_back("Atout");

		for (uiCarteValeur = 0; uiCarteValeur <= 21; uiCarteValeur++)
		{
			unique_ptr<CCarte> pcNouvelleCarte;

			if (uiCarteValeur == 0)
			{
				pcNouvelleCarte = make_unique<CCarte>("Atout", uiCarteValeur, "L'excuse");
			}
			else {
				pcNouvelleCarte = make_unique<CCarte>("Atout", uiCarteValeur);
			}

			vcPaquet.push_back(move(pcNouvelleCarte));
		}
	}
};

#endif 