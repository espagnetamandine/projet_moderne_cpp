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
	
	//virtual void REG_NombreDePoints()=0;
	virtual void REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet> paquet)=0;
	virtual bool REG_PremiereCarte(const CCarte& carte)=0;
	virtual bool REG_CarteValide(const CCarte& carte)=0;
	virtual int REG_GagnePli(map<CJoueur*, unique_ptr<CCarte>>& mJEU_pli)=0;
	virtual void REG_CalculPoints()=0;
	virtual CJoueur REG_CalculGagnant()=0;
	virtual bool REG_FinDeManche()=0;
	virtual bool REG_FinDePartie()=0;
	virtual void REG_AfficherPoints()=0;
	virtual void REG_AfficherGagnant()=0;
};
#endif 
