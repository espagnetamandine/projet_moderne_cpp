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

	// ATTRIBUTS

	string sREG_Atout;

	// METHODES SPECIALISEES

	int REG_PremierTourEnchere(vector<unique_ptr<CJoueur>>& joueurs, unsigned int uiJoueurCourant, const CCarte& carteDuMilieu, map<unique_ptr<CEquipe>, int>& points);
	int REG_DeuxiemeTourEnchere(vector<unique_ptr<CJoueur>>& joueurs, unsigned int uiJoueurCourant, const string& sCouleurRetourne, map<unique_ptr<CEquipe>, int>& points);
	void REG_SetAtout(string sNouveauAtout);
	
	unsigned int REG_ObtenirForceAtout(const unsigned int& uiValeur);
	unsigned int REG_ObtenirForceNormal(const unsigned int& uiValeur);
	unsigned int REG_ObtenirMeilleurCarteTapis(const vector<unique_ptr<CCarte>>& cartesDuPli, const string& sCouleurDemandee, const string& sAtout);

public:

	// CONSTRUCTEURS ET DESTRUCTEURS

	CRegleBelote() = default;
	~CRegleBelote() = default;

	// SETTERS ET GETTERS

	virtual bool REG_SetNbJoueur(unsigned int uiNbJoueurs);

	// METHODES DE CREGLE

	virtual void REG_DebutPartie(unique_ptr<CPaquet>& paquet,vector<unique_ptr<CJoueur>>& joueurs,map<unique_ptr<CEquipe>, int>& points);
	virtual void REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points);
	virtual bool REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& points);
	
	virtual unsigned int REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int& uiJEU_IdJoueurCourrant);
	virtual bool REG_ConditionFinManche(const vector<unique_ptr<CJoueur>>& joueurs);

	virtual void REG_JoueurSuivant(unsigned int uiIndiceJoueur); // n’est jamais appelé directement, change indice joueur courant
	virtual void REG_MettreEnPlacePioche();

	virtual void REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet);
	virtual bool REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& pPaquetJoueur, const unique_ptr<CPaquet>& pPli, const vector<unsigned int>& vuIdJoueurPli);

	virtual unsigned int REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli); // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
	virtual void REG_CalculerPointsPli(unique_ptr<CPaquet>& pPli, unsigned int uiIndiceJoueurGagnantPli, map<unique_ptr<CEquipe>, int>& points);
	virtual void REG_CalculerPointsManche(); // si nécessaire

	virtual void REG_RemettreCartesDansPaquet(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet);

	// AFFICHAGE

	virtual void REG_AfficherGagnantPartie(map<unique_ptr<CEquipe>, int>& points, const vector<unique_ptr<CJoueur>>& joueurs);

	virtual void REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPli);

	virtual void REG_AfficherAfficherPli(unique_ptr<CPaquet> pPli, vector<unsigned int> vuIdJoueurPli);
	virtual void REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur);
	virtual void REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& mJEU_points);

};
#endif

