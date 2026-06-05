#ifndef _CPAQUETDecorateurJeu52_H
#define _CPAQUETDecorateurJeu52_H

#include "CPaquetDecorateur.h"

using namespace std;

class CPaquetDecorateurJeu52 : public CPaquetDecorateur {
public:
	CPaquetDecorateurJeu52(unique_ptr<CPaquet> paquet) : CPaquetDecorateur(move(paquet))
	{
		PAQ_Ajouter52Cartes();
	}

private:
	void PAQ_Ajouter52Cartes()
	{
		unsigned int uiCarteValeur;

		vector<unique_ptr<CCarte>>& vcPaquet = getPAQ_cartes();
		vector<string>& vsCouleursGlobales = getPAQ_couleurs();

		vector<string> vsCouleursAAjouter = { "Coeur", "Carreau", "Trefle", "Pique" };

		for (const string& sNouvelleCouleur : vsCouleursAAjouter) {
			vsCouleursGlobales.push_back(sNouvelleCouleur);

			for (uiCarteValeur = 0; uiCarteValeur < 13; uiCarteValeur++)
			{
				unique_ptr<CCarte> nouvelleCarte = make_unique<CCarte>(sNouvelleCouleur, uiCarteValeur + 1);

				vcPaquet.push_back(move(nouvelleCarte));
			}
		}	
	}
};

#endif 