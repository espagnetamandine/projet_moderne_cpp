#ifndef _CREGLE_H
#define _CREGLE_H

#include "CCarte.h"
#include "CPaquet.h"
#include "CJoueur.h"
// #include "CEquipe.h"
#include "CJeu.h"
#include <vector>
#include <map>

class CRegle {
protected:
	CPaquet pREG_paquet_de_cartes; // CPaquet virtuelle pure 
	vector<CJoueur> vjREG_joueurs;
	unsigned int uiREG_IdxJoueurCourrant;
	map<CJoueur, CEquipe> vjREG_equipes; //CEquipe pas encore definie
	map<CJoueur, int> vjREG_points;
	map<CJoueur, CCarte> mREG_pli;
	
public:
	CRegle() {};
	~CRegle() {};

	/*
	CPaquet JEU_GetPaquet() { return pJEU_paquet_de_cartes; }
	vector<CJoueur> JEU_GetJoueurs() { return vjJEU_joueurs; }
	map<CJoueur, int> JEU_GetPoints() { return vjJEU_points; }
	map<CJoueur, CCarte> JEU_GetPli() { return mJEU_pli; }
	*/
	
	virtual void REG_JouerPartie()=0;
	//virtual void REG_NombreDePoints()=0;
	virtual void REG_DistribuerCartes()=0;
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