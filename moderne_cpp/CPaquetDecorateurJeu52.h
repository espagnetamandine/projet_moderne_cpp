#ifndef _CPAQUETDecorateurJeu52_H
#define _CPAQUETDecorateurJeu52_H

#include "CPaquetDecorateur.h"

using namespace std;

class CPaquetDecorateurJeu52 : public CPaquetDecorateur {
public:

	// Constructeurs et destructeurs

	CPaquetDecorateurJeu52(unique_ptr<CPaquet> pPaquet) : CPaquetDecorateur(move(pPaquet))
	{
		PAQ_Ajouter52Cartes();
	}

private:

	// Méthodes

	void PAQ_Ajouter52Cartes()
	{
		unsigned int uiCarteValeur;

		vector<unique_ptr<CCarte>>& vcPaquet = PAQ_GetCartes();
		vector<string>& vsCouleursGlobales = PAQ_GetCouleurs();

		vector<string> vsCouleursAAjouter = { "Coeur", "Carreau", "Trefle", "Pique" };

		for (const string& sNouvelleCouleur : vsCouleursAAjouter) {
			vsCouleursGlobales.push_back(sNouvelleCouleur);

			for (uiCarteValeur = 0; uiCarteValeur < 13; uiCarteValeur++)
			{
				unique_ptr<CCarte> pcNouvelleCarte = make_unique<CCarte>(sNouvelleCouleur, uiCarteValeur + 1);

				vcPaquet.push_back(move(pcNouvelleCarte));
			}
		}	
	}
};

#endif 