#ifndef _CREGLETAROT_H
#define _CREGLETAROT_H

#include "CRegle.h"
#include <map>

class CRegleTarot : public CRegle {
private:

public:
	CRegleTarot();
	~CRegleTarot();

	virtual void REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet> paquet);
	virtual bool REG_PremiereCarte(unique_ptr<CCarte>& carte);
	virtual bool REG_CarteValide(unique_ptr<CCarte>& carte);
	virtual int REG_GagnePli(map<CJoueur*, unique_ptr<CCarte>>& mJEU_pli);
	virtual void REG_CalculPoints();
	virtual CJoueur REG_CalculGagnant();
	virtual bool REG_FinDeManche();
	virtual bool REG_FinDePartie();
	virtual void REG_AfficherPoints();
	virtual void REG_AfficherGagnant();
};
#endif

