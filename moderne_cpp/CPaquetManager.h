#ifndef _CPAQUETMANAGER_H
#define _CPAQUETMANAGER_H

#include <memory>
#include <string>
#include <stdexcept>

#include "CPaquetBase.h"
#include "CPaquetDecorateurJeu32.h"
#include "CPaquetDecorateurJeu52.h"
#include "CPaquetDecorateurAjouterJoker.h"
#include "CPaquetDecorateurTarot.h"

using namespace std;

class CPaquetManager {
public:
	static unique_ptr<CPaquet> creerPaquet(const string& sTypeJeu)
	{
		unique_ptr<CPaquet> pPaquet = make_unique<CPaquetBase>();

		if (sTypeJeu == "Belote" or 
			sTypeJeu == "Manille" or
			sTypeJeu == "32")
		{
			pPaquet = make_unique<CPaquetDecorateurJeu32>(move(pPaquet));
		}
		else if (sTypeJeu == "Poker" or 
			sTypeJeu == "Bridge" or
			sTypeJeu == "Dame de pique" or 
			sTypeJeu == "52")
		{
			pPaquet = make_unique<CPaquetDecorateurJeu52>(move(pPaquet));
		}
		else if (sTypeJeu == "Rummy" or 
			sTypeJeu == "54")
		{
			pPaquet = make_unique<CPaquetDecorateurJeu52>(move(pPaquet));
			pPaquet = make_unique<CPaquetDecorateurAjouterJoker>(move(pPaquet));
		}
		else if (sTypeJeu == "Tarot")
		{
			pPaquet = make_unique<CPaquetDecorateurJeu52>(move(pPaquet));
			pPaquet = make_unique<CPaquetDecorateurTarot>(move(pPaquet));
		}
		else
		{
			throw invalid_argument("Type de jeu inconnu : " + sTypeJeu);
		}

		return pPaquet;
	}
};

#endif