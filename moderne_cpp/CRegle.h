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

public:
	// Constructeurs et destructeurs

	CRegle() = default;
	~CRegle() = default;

	// Méthodes de jeu

	virtual void REG_DebutPartie(unique_ptr<CPaquet>& upPaquetPrincipal, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe) = 0;
	virtual bool REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& muPointsEquipe) = 0;
	virtual unsigned int REG_DebutManche(unique_ptr<CPaquet>& upPaquetPrincipal, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unsigned int& uiIdJoueurCourrant) = 0;
	virtual bool REG_ConditionFinManche(const vector<unique_ptr<CJoueur>>& vuJoueurs) = 0;
	virtual bool REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& upPaquetJoueur, const unique_ptr<CPaquet>& upPli, const vector<unsigned int>& vuIdJoueurPli) = 0;
	
	// Méthodes d'entre-jeu
	virtual void REG_DebutPartie(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points) = 0; // appelle constituer équipe
	virtual bool REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& points) = 0;
	virtual unsigned int REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int& uiJEU_IdJoueurCourrant) = 0; // ajouter 1 à la manche
	virtual bool REG_ConditionFinManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs) = 0;

	virtual void REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int uiIndincePreneur) = 0;
	virtual void REG_MettreEnPlacePioche() = 0;

	virtual unsigned int REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& upPli, vector<unsigned int>& vuIdJoueurPli) = 0;
	virtual void REG_CalculerPointsPli(unique_ptr<CPaquet>& upPli, unsigned int uiIndiceJoueurGagnantPli, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unique_ptr<CPaquet>& upDefausse) = 0;
	virtual void REG_CalculerPointsManche(unique_ptr<CPaquet>& upPli, unsigned int uiIndiceJoueurGagnantPli, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unique_ptr<CPaquet>& upDefausse, const vector<unique_ptr<CJoueur>>& vuJoueurs) = 0;

	// Mise en place

	virtual bool REG_VerificationNbJoueur(unsigned int uiNbJoueurs) = 0;
	virtual void REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe) = 0;
	virtual void REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& vuJoueurs, unique_ptr<CPaquet>& upPaquetPrincipal) = 0;
	virtual void REG_RemettreCartesDansPaquet(vector<unique_ptr<CJoueur>>& vuJoueurs, unique_ptr<CPaquet>& upPaquetPrincipal) = 0;
	virtual void REG_MettreEnPlacePioche() = 0;

	virtual unsigned int REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli) = 0; // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
	virtual void REG_CalculerPointsPli(unique_ptr<CPaquet>& pPlie, map<unique_ptr<CEquipe>, int>& points, unsigned int uiIndinceGagnant, vector<unsigned int>& vuIdJoueurPli) = 0;
	virtual void REG_CalculerPointsManche(map<unique_ptr<CEquipe>, int>& points, unsigned int uiIndicePreneur, unsigned int uiAnnonceMax, unique_ptr<CPaquet>& pDernierPli, unsigned int uiIndiceGagnantDernierPli, unique_ptr<CPaquet>& pCartesPreneur) = 0; // si nécessaire
	// Affichage

	virtual void REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vuJoueurs, unsigned int uiIndiceJoueurGagnantPli) = 0;
	virtual void REG_AfficherGagnantManche(map<unique_ptr<CEquipe>, int>& muPointsEquipe, const vector<unique_ptr<CJoueur>>& vuJoueurs) = 0;
	virtual void REG_AfficherGagnantPartie(map<unique_ptr<CEquipe>, int>& muPointsEquipe, const vector<unique_ptr<CJoueur>>& vuJoueurs) = 0;
	virtual void REG_AfficherMainJoueur(unsigned int uiIdJoueur, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe) = 0;
	virtual void REG_AfficherAfficherPli(unique_ptr<CPaquet> upPli, vector<unsigned int> vuIdJoueurPli) = 0;
	virtual void REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& muPointsEquipe) = 0;

};

#endif 
