#ifndef _CREGLEDAMEDEPIQUE_H
#define _CREGLEDAMEDEPIQUE_H

#include "CRegle.h"
#include <map>

class CRegleDameDePique : public CRegle {
private:
	vector<unique_ptr<CCarte>> vTroisCartes;

public:
	CRegleDameDePique() = default;
	~CRegleDameDePique() = default;
	
	virtual bool REG_SetNbJoueur(unsigned int uiNbJoueurs);

	virtual void REG_DebutPartie(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points);
	virtual bool REG_ConditionFinPartie();

	// renvoie l'indice du premier joueur ou 0 (ou aléatoire, cf CRegleDameDePique.cpp) si pas de joueur en particulier
	virtual unsigned int REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int& uiJEU_IdJoueurCourrant);
	virtual bool REG_ConditionFinManche();

	virtual void REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points);
	virtual void REG_MettreEnPlacePioche();

	virtual void REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet);
	
	virtual bool REG_PremiereCarte(CCarte& carte);
	virtual bool REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& pPaquetJoueur);

	virtual unsigned int REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli); // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
	virtual void REG_CalculerPointsPli();
	virtual void REG_CalculerPointsManche(); // si nécessaire

	virtual void REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPli);
	virtual void REG_AfficherGagnantPartie(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPartie);
	virtual void REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur); // appelle afficherpli
	virtual void REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& mJEU_points);
};
#endif

