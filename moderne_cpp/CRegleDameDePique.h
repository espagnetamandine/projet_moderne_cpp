#ifndef _CREGLEDAMEDEPIQUE_H
#define _CREGLEDAMEDEPIQUE_H

#include "CRegle.h"

class CRegleDameDePique : public CRegle {
private:

public:
	CRegleDameDePique();
	~CRegleDameDePique();
	
	virtual void REG_JouerPartie();
	//virtual void REG_NombreDePoints();
	virtual void REG_DistribuerCartes();
	virtual bool REG_PremiereCarte(CCarte carte);
	virtual bool REG_CarteValide(CCarte carte);
	virtual int REG_GagnePli();
	virtual void REG_CalculPoints();
	virtual CJoueur REG_CalculGagnant();
	virtual bool REG_FinDeManche();
	virtual bool REG_FinDePartie();
	virtual void REG_AfficherPoints();
	virtual void REG_AfficherGagnant();
};
#endif 