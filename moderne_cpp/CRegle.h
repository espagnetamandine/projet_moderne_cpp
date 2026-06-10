#ifndef _CREGLE_H
#define _CREGLE_H

#include "CCarte.h"
#include "CPaquet.h"
#include "CJoueur.h"

#include <vector>
#include <map>

class CRegle {
public:
	CRegle();
	~CRegle();

	
	virtual void REG_DebutPartie() = 0;
	virtual bool REG_ConditionFINPartie() = 0;
	virtual void REG_DebutManche() = 0;
	virtual bool REG_ConditionFinManche() = 0;
	virtual void REG_JoueurSuivant(unsigned int uiIndiceJueur) = 0;
	virtual void REG_ConstituerEquipes() = 0;
	virtual void REG_MettreEnPlacePioche() = 0;
	virtual void REG_Distribuer() = 0;
	virtual unsigned int REG_DeterminerIndiceGagnantPli() = 0;
	virtual bool REG_CarteValide() = 0;
	virtual void REG_CalculerPointsPli() = 0;
	virtual void REG_CalculerPointsManche() = 0;
	virtual void REG_AfficherGagnantPli() = 0;
	virtual void REG_AfficherGagnantPartie() = 0;
	virtual void REG_AfficherMainJoueur() = 0; 
	virtual void REG_AfficherPoints() = 0;
};




#endif 
