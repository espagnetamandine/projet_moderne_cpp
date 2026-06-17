#ifndef _CREGLEMANAGER_H
#define _CREGLEMANAGER_H

#include <stdexcept>

#include "CRegle.h"
#include "CRegleDameDePique.h"
#include "CRegleTarot.h"
#include "CRegleBelote.h"

using namespace std;

class CRegleManager {
public:
	static unique_ptr<CRegle> REG_CreerRegle(const string& sTypeJeu)
	{
		unique_ptr<CRegle> pRegle = nullptr;

		if (sTypeJeu == "Dame de pique")
		{
			pRegle = make_unique<CRegleDameDePique>();
		}
		else if (sTypeJeu == "Tarot")
		{
			//pRegle = make_unique<CRegleTarot>();
		}
		else if (sTypeJeu == "Belote")
		{
			pRegle = make_unique<CRegleBelote>();
		}
		else
		{
			throw invalid_argument("Type de jeu inconnu : " + sTypeJeu);
		}

		return pRegle;
	}
};

#endif