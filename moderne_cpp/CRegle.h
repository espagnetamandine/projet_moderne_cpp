#ifndef _CREGLE_H
#define _CREGLE_H

#include "CPaquet.h"
#include "CConsole.h"
#include "CJoueur.h"
#include "CEquipe.h"

#include <vector>
#include <map>
using namespace std;

class CRegle {
protected :
	unsigned int uiNbJoueurPossible;

public:
	CRegle() = default;
	~CRegle() = default;
	
	virtual bool REG_SetNbJoueur(unsigned int uiNbJoueurs) = 0;
	virtual void REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points) = 0;

	virtual void REG_DebutPartie(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points) = 0; // appelle constituer équipe
	virtual bool REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& points) = 0;
	
	virtual unsigned int REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int& uiJEU_IdJoueurCourrant) = 0; // ajouter 1 à la manche
	virtual bool REG_ConditionFinManche(const vector<unique_ptr<CJoueur>>& joueurs) = 0;

	virtual void REG_MettreEnPlacePioche() = 0;

	virtual void REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet) = 0;
	
	virtual bool REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& pPaquetJoueur) = 0;
	
	virtual unsigned int REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli) = 0; // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
	virtual void REG_CalculerPointsPli() = 0;
	virtual void REG_CalculerPointsManche() = 0; // si nécessaire

	// AFFICHAGE


	virtual void REG_AfficherGagnantPartie(map<unique_ptr<CEquipe>, int>& points, const vector<unique_ptr<CJoueur>>& joueurs) = 0;

	virtual void REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPli) = 0;
	virtual void REG_AfficherAfficherPli(unique_ptr<CPaquet> pPli, vector<unsigned int> vuIdJoueurPli) = 0;
	virtual void REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur) = 0; 
	virtual void REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& mJEU_points) = 0;

};

#endif 
