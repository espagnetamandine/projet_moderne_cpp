#ifndef _CREGLEDAMEDEPIQUE_H
#define _CREGLEDAMEDEPIQUE_H

#include "CRegle.h"

class CRegleDameDePique : public CRegle {
private:

public:
	CRegleDameDePique() {};
	~CRegleDameDePique() {};
	virtual void REG_NombreDePoints();
	virtual void REG_DistribuerCartes();
	virtual bool REG_PremiereCarte();
	virtual bool REG_CarteValide();
	virtual int REG_GagnePli();
	virtual void REG_CalculPoints();
};
#endif 