#ifndef _CREGLEDAMEDEPIQUE_H
#define _CREGLEDAMEDEPIQUE_H

#include "CRegle.h"

#include <map>
#include <string>
#include <vector>
#include <memory>

class CPaquet;
class CJoueur;
class CCarte;
class CEquipe;

class CRegleDameDePique : public CRegle {
private:
	vector<unique_ptr<CCarte>> vTroisCartes;

	bool bPremiereCarte = true;

public:
	CRegleDameDePique() = default;
	~CRegleDameDePique() = default;
	
	virtual bool REG_SetNbJoueur(unsigned int uiNbJoueurs);

	virtual void REG_DebutPartie(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points);
	virtual bool REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& points);

	// renvoie l'indice du premier joueur ou 0 (ou aléatoire, cf CRegleDameDePique.cpp) si pas de joueur en particulier
	virtual unsigned int REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int& uiJEU_IdJoueurCourrant);
	virtual bool REG_ConditionFinManche(const vector<unique_ptr<CJoueur>>& joueurs);

	virtual void REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points);
	virtual void REG_MettreEnPlacePioche();

	virtual void REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet);
	
	bool REG_PremiereCarte(CCarte& carte);
	virtual bool REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& pPaquetJoueur, const unique_ptr<CPaquet>& pPli, const vector<unsigned int>& vuIdJoueurPli);

	virtual unsigned int REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli); // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
	virtual void REG_CalculerPointsPli(unique_ptr<CPaquet>& pPli, unsigned int uiIndiceJoueurGagnantPli, map<unique_ptr<CEquipe>, int>& points);
	virtual void REG_CalculerPointsManche(); // si nécessaire

	virtual void REG_RemettreCartesDansPaquet(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet);

	virtual void REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPli);
	virtual void REG_AfficherGagnantPartie(map<unique_ptr<CEquipe>, int>& points, const vector<unique_ptr<CJoueur>>& joueurs);
	virtual void REG_AfficherAfficherPli(unique_ptr<CPaquet> pPli, vector<unsigned int> vuIdJoueurPli) {};
	virtual void REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur); // appelle afficherpli
	virtual void REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& mJEU_points);
};
#endif

