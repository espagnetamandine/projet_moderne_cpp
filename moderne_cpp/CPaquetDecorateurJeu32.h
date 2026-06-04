#ifndef _CPAQUETDecorateurJeu32_H
#define _CPAQUETDecorateurJeu32_H

#include "CPaquetDecorateur.h"

using namespace std;

class CPaquetDecorateurJeu32 : public CPaquetDecorateur {
public:
	CPaquetDecorateurJeu32(unique_ptr<CPaquet> paquet) : CPaquetDecorateur(move(paquet))
	{
		PAQ_Ajouter32Cartes();
	}

private:
	void PAQ_Ajouter32Cartes()
	{
		unsigned int uiCarteValeur;

		vector<CCarte>& vcPaquet = getPAQ_cartes();
		vector<string>& vsCouleursGlobales = getPAQ_couleurs();

		vector<string> vsCouleursAAjouter = { "Coeur", "Carreau", "Trefle", "Pique" };

		for (const string& sNouvelleCouleur : vsCouleursAAjouter) {
			vsCouleursGlobales.push_back(sNouvelleCouleur);

			vcPaquet.push_back(CCarte(sNouvelleCouleur, 1));

			for (uiCarteValeur = 6; uiCarteValeur < 13; uiCarteValeur++)
			{
				vcPaquet.push_back(CCarte(sNouvelleCouleur, uiCarteValeur + 1));
			}
		}
	}
};

#endif 