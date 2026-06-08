#ifndef _CREGLETAROT_H
#define _CREGLETAROT_H

#include "CRegle.h"

class CRegleTarot : public CRegle {
private:

public:
	CRegleTarot();
	~CRegleTarot();

	//virtual void REG_NombreDePoints();
	virtual void REG_DistribuerCartes(vector<CJoueur> joueurs, CPaquet paquet);
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
