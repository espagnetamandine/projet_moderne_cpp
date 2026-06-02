#ifndef _CREGLE_H
#define _CREGLE_H

#include "CCarte.h"
#include "CPaquet.h"
#include "CJoueur.h"
#include <vector>
#include <map>

class CRegle {
private:

public:
	CRegle() {};
	~CRegle() {};
	virtual void REG_NombreDePoints()=0;
	virtual void REG_DistribuerCartes()=0;
	virtual bool REG_PremiereCarte()=0;
	virtual bool REG_CarteValide()=0;
	virtual int REG_GagnePli()=0;
	virtual void REG_CalculPoints()=0;
};
#endif 