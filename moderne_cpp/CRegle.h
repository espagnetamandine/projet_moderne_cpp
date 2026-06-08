#ifndef _CREGLE_H
#define _CREGLE_H

#include "CCarte.h"
#include "CPaquet.h"
#include "CJoueur.h"

#include <vector>

class CRegle {	
public:
	CRegle();
	~CRegle();
	
	//virtual void REG_NombreDePoints()=0;
	virtual void REG_DistribuerCartes(vector<CJoueur> joueurs, CPaquet paquet)=0;
	virtual bool REG_PremiereCarte(CCarte carte)=0;
	virtual bool REG_CarteValide(CCarte carte)=0;
	virtual int REG_GagnePli()=0;
	virtual void REG_CalculPoints()=0;
	virtual CJoueur REG_CalculGagnant()=0;
	virtual bool REG_FinDeManche()=0;
	virtual bool REG_FinDePartie()=0;
	virtual void REG_AfficherPoints()=0;
	virtual void REG_AfficherGagnant()=0;
};
#endif 