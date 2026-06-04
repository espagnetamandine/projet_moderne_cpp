#ifndef _CREGLEDAMEDEPIQUE_H
#define _CREGLEDAMEDEPIQUE_H

#include "CRegle.h"

class CRegleDameDePique : public CRegle {
private:

public:
	CRegleDameDePique();
	~CRegleDameDePique();
	virtual void REG_NombreDePoints();
	virtual void REG_DistribuerCartes(CJeu<CRegle>& jeu);
	virtual bool REG_PremiereCarte(CCarte carte);
	virtual bool REG_CarteValide();
	virtual int REG_GagnePli();
	virtual void REG_CalculPoints();
	virtual CJoueur REG_CalculGagnant();
	virtual bool REG_FinDePartie();
};
#endif 