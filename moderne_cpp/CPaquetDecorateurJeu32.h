#ifndef _CPAQUETDecorateurJeu32_H
#define _CPAQUETDecorateurJeu32_H

#include "CPaquetDecorateur.h"

using namespace std;

class CPaquetDecorateurJeu32 : public CPaquetDecorateur {
public:
	CPaquetDecorateurJeu32(unique_ptr<CPaquet> pPaquet) : CPaquetDecorateur(move(pPaquet))
	{
		PAQ_Ajouter32Cartes();
	}

private:
	void PAQ_Ajouter32Cartes()
	{
		unsigned int uiCarteValeur;

		vector<unique_ptr<CCarte>>& vcPaquet = getPAQ_Cartes();
		vector<string>& vsCouleursGlobales = getPAQ_Couleurs();

		vector<string> vsCouleursAAjouter = { "Coeur", "Carreau", "Trefle", "Pique" };

		for (const string& sNouvelleCouleur : vsCouleursAAjouter) {
			vsCouleursGlobales.push_back(sNouvelleCouleur);

			unique_ptr<CCarte> pcNouvelleCarte = make_unique<CCarte>(sNouvelleCouleur, 1);

			vcPaquet.push_back(move(pcNouvelleCarte));

			for (uiCarteValeur = 6; uiCarteValeur < 13; uiCarteValeur++)
			{
				unique_ptr<CCarte> pcNouvelleCarte = make_unique<CCarte>(sNouvelleCouleur, uiCarteValeur + 1);

				vcPaquet.push_back(move(pcNouvelleCarte));
			}
		}
	}
};

#endif 