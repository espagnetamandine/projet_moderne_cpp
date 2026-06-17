#ifndef _CREGLETAROT_H
#define _CREGLETAROT_H

#include "CRegle.h"

#include <map>
#include <string>
#include <vector>
#include <memory>

class CPaquet;
class CJoueur;
class CCarte;
class CEquipe;

class CRegleTarot : public CRegle {
private:
	// Attributs

	unique_ptr<CPaquet> upREG_Chien;
	map<unique_ptr<CEquipe>, int> muREG_PointsManche;
	unsigned int uiREG_AnnonceMax;
	unsigned int uiREG_IndicePreneur;

	// Méthodes spécialisées

	bool REG_PremiereCarte(CCarte& carte);
	void REG_ChoixCarteChien(vector<unique_ptr<CJoueur>>& vuJoueurs, unsigned uiIndicePreneur, unsigned uiAnnonceMax, map<unique_ptr<CEquipe>, int>& muPointsEquipe);

public:
	
	// Constructeurs et destructeurs

	CRegleTarot()= default;
	~CRegleTarot()= default;
	
	//Méthodes de jeu

	void REG_DebutPartie(unique_ptr<CPaquet>& upPaquetPrincipal, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe);
	bool REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& muPointsEquipe);
	unsigned int REG_DebutManche(unique_ptr<CPaquet>& upPaquetPrincipal, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unsigned int& uiIdJoueurCourrant);
	bool REG_ConditionFinManche(const vector<unique_ptr<CJoueur>>& vuJoueurs);
	bool REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& upPaquetJoueur, const unique_ptr<CPaquet>& upPli, const vector<unsigned int>& vuIdJoueurPli);
	
	// Méthodes d'entre-jeu

	unsigned int REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& upPli, vector<unsigned int>& vuIdJoueurPli);
	void REG_CalculerPointsPli(unique_ptr<CPaquet>& upPli, unsigned int uiIndiceJoueurGagnantPli, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unique_ptr<CPaquet>& upDefausse, const vector<unique_ptr<CJoueur>>& vuJoueurs);
	void REG_CalculerPointsManche(unique_ptr<CPaquet>& upPli, unsigned int uiIndiceJoueurGagnantPli, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unique_ptr<CPaquet>& upDefausse, const vector<unique_ptr<CJoueur>>& vuJoueurs);
	
	// Mise en place

	void REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe);
	void REG_MettreEnPlacePioche(unique_ptr<CPaquet>& upPaquetPrincipal, vector<unique_ptr<CJoueur>>& vuJoueurs);
	void REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& vuJoueurs, unique_ptr<CPaquet>& upPaquetPrincipal);
	bool REG_VerificationNbJoueur(unsigned int uiNbJoueurs);
	void REG_RemettreCartesDansPaquet(vector<unique_ptr<CJoueur>>& vuJoueurs, unique_ptr<CPaquet>& upPaquetPrincipal);
	
	// Affichage

	void REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vuJoueurs, unsigned int uiIndiceJoueurGagnantPli);
	void REG_AfficherGagnantManche(map<unique_ptr<CEquipe>, int>& muPointsEquipe, const vector<unique_ptr<CJoueur>>& vuJoueurs);
	void REG_AfficherGagnantPartie(map<unique_ptr<CEquipe>, int>& muPointsEquipe, const vector<unique_ptr<CJoueur>>& vuJoueurs);
	void REG_AfficherMainJoueur(unsigned int uiIdJoueur, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe);
	void REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& muPointsEquipe, const vector<unique_ptr<CJoueur>>& vuJoueurs);
	void REG_AfficherAfficherPli(unique_ptr<CPaquet>& upPli, vector<unsigned int> vuIdJoueurPli);

};
#endif

