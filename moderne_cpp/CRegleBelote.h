#ifndef _CREGLEBelote_H
#define _CREGLEBelote_H

#include "CRegle.h"

#include <map>
#include <string>
#include <vector>
#include <memory>

class CPaquet;
class CJoueur;
class CCarte;
class CEquipe;

class CRegleBelote : public CRegle {
private:

	// Attributs

	string sREG_Atout;
	unsigned int uiREG_NumeroEquipePreneuse = 0;
	int iREG_PointsMancheEquipe1 = 0;
	int iREG_PointsMancheEquipe2 = 0;

	// Méthodes spécialisées

	int REG_PremierTourEnchere(vector<unique_ptr<CJoueur>>& joueurs, unsigned int uiJoueurCourant, const CCarte& carteDuMilieu, map<unique_ptr<CEquipe>, int>& muPointsEquipe);
	int REG_DeuxiemeTourEnchere(vector<unique_ptr<CJoueur>>& joueurs, unsigned int uiJoueurCourant, const string& sCouleurRetourne, map<unique_ptr<CEquipe>, int>& muPointsEquipe);
	void REG_SetAtout(string sNouveauAtout);
	
	unsigned int REG_ObtenirForceAtout(const unsigned int& uiValeur);
	unsigned int REG_ObtenirForceNormal(const unsigned int& uiValeur);
	unsigned int REG_ObtenirMeilleurCarteTapis(const vector<unique_ptr<CCarte>>& cartesDuPli, const string& sCouleurDemandee, const string& sAtout);

public:

	// Constructeurs et destructeurs

	CRegleBelote() = default;
	~CRegleBelote() = default;

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
	virtual void REG_AfficherMainJoueur(unsigned int uiIdJoueur, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe) ;

	virtual void REG_AfficherAfficherPli(unique_ptr<CPaquet>& upPli, vector<unsigned int> vuIdJoueurPli);
	virtual void REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& muPointsEquipe);

};
#endif

