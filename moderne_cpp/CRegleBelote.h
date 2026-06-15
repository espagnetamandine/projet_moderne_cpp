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
	string sREG_Atout;

	void REG_DistribuerCinqCartes(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs);
	int REG_PremierTourEnchere(vector<unique_ptr<CJoueur>>& joueurs, unsigned int uiJoueurCourant, const CCarte& carteDuMilieu, map<unique_ptr<CEquipe>, int>& points);
	int REG_DeuxiemeTourEnchere(vector<unique_ptr<CJoueur>>& joueurs, unsigned int uiJoueurCourant, const string& sCouleurRetourne);

public:
	CRegleBelote() = default;
	~CRegleBelote() = default;

	virtual bool REG_SetNbJoueur(unsigned int uiNbJoueurs);

	virtual void REG_DebutPartie(
		unique_ptr<CPaquet>& paquet,
		vector<unique_ptr<CJoueur>>& joueurs,
		map<unique_ptr<CEquipe>, int>& points
	);

	virtual bool REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& points);
	virtual unsigned int REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int& uiJEU_IdJoueurCourrant);
	virtual bool REG_ConditionFinManche();

	virtual void REG_JoueurSuivant(unsigned int uiIndiceJoueur); // n’est jamais appelé directement, change indice joueur courant
	virtual void REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points);
	virtual void REG_MettreEnPlacePioche();

	virtual void REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet);
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

