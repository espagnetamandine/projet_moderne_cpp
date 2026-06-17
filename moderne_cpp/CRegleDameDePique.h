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
	// Attributs

	vector<unique_ptr<CCarte>> vTroisCartes;

	bool bPremiereCarte = true;

	// Méthodes spécialisées

	bool REG_PremiereCarte(CCarte& pcCarte);
	
public:
	// Constructeurs et destructeurs

	CRegleDameDePique() = default;
	~CRegleDameDePique() = default;
	
	// Méthodes de jeu

	virtual void REG_DebutPartie(unique_ptr<CPaquet>& upPaquetPrincipal, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe);
	virtual bool REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& muPointsEquipe);
	virtual unsigned int REG_DebutManche(unique_ptr<CPaquet>& upPaquetPrincipal, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unsigned int& uiIdJoueurCourrant);
	virtual bool REG_ConditionFinManche(const vector<unique_ptr<CJoueur>>& vuJoueurs);
	virtual bool REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& upPaquetJoueur, const unique_ptr<CPaquet>& upPli, const vector<unsigned int>& vuIdJoueurPli);

	// Méthodes d'entre-jeu

	virtual unsigned int REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& upPli, vector<unsigned int>& vuIdJoueurPli);
	virtual void REG_CalculerPointsPli(unique_ptr<CPaquet>& upPli, unsigned int uiIndiceJoueurGagnantPli, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unique_ptr<CPaquet>& upDefausse);
	virtual void REG_CalculerPointsManche(unique_ptr<CPaquet>& upPli, unsigned int uiIndiceJoueurGagnantPli, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unique_ptr<CPaquet>& upDefausse, const vector<unique_ptr<CJoueur>>& vuJoueurs);

	// Mise en place

	virtual bool REG_VerificationNbJoueur(unsigned int uiNbJoueurs);
	virtual void REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe);
	virtual void REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& vuJoueurs, unique_ptr<CPaquet>& upPaquetPrincipal);
	virtual void REG_RemettreCartesDansPaquet(vector<unique_ptr<CJoueur>>& vuJoueurs, unique_ptr<CPaquet>& upPaquetPrincipal);
	virtual void REG_MettreEnPlacePioche(unique_ptr<CPaquet>& upPaquet, vector<unique_ptr<CJoueur>>& vuJoueurs);

	// Affichage

	virtual void REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vuJoueurs, unsigned int uiIndiceJoueurGagnantPli);
	virtual void REG_AfficherGagnantManche(map<unique_ptr<CEquipe>, int>& muPointsEquipe, const vector<unique_ptr<CJoueur>>& vuJoueurs);
	virtual void REG_AfficherGagnantPartie(map<unique_ptr<CEquipe>, int>& muPointsEquipe, const vector<unique_ptr<CJoueur>>& vuJoueurs);
	virtual void REG_AfficherMainJoueur(unsigned int uiIdJoueur, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe);

	virtual void REG_AfficherAfficherPli(unique_ptr<CPaquet>& upPli, vector<unsigned int> vuIdJoueurPli);
	virtual void REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& muPointsEquipe, const vector<unique_ptr<CJoueur>>& vuJoueurs);
};
#endif

