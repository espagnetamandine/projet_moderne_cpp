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
	unique_ptr<CPaquet> pREG_Chien;
	map<unique_ptr<CEquipe>, int> mREG_PointsManche;
public:
	CRegleTarot()= default;
	~CRegleTarot()= default;
	

	bool REG_SetNbJoueur(unsigned int uiNbJoueurs);

	void REG_DebutPartie(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points); // appelle constituer équipe
	bool REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& points);
	unsigned int REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int& uiJEU_IdJoueurCourrant); // ajouter 1 à la manche
	bool REG_ConditionFinManche(vector<unique_ptr<CJoueur>>& joueurs);

	
	void REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int uiIndincePreneur);
	void REG_MettreEnPlacePioche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs);

	void REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet);
	void REG_ChoixCarteChien(vector<unique_ptr<CJoueur>>& joueurs, unsigned uiIndicePreneur, unsigned uiAnnonceMax);

	bool REG_PremiereCarte(CCarte& carte);

	bool REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& pPaquetJoueur);

	unsigned int REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli); // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
	void REG_CalculerPointsPli(unique_ptr<CPaquet>& pPlie, map<unique_ptr<CEquipe>, int>& points, unsigned int uiIndinceGagnant, vector<unsigned int>& vuIdJoueurPli);
	void REG_CalculerPointsManche(map<unique_ptr<CEquipe>, int>& points, unsigned int uiIndicePreneur, unsigned int uiAnnonceMax, unique_ptr<CPaquet>& pDernierPli, unsigned int uiIndiceGagnantDernierPli, unique_ptr<CPaquet>& pCartesPreneur,vector<unique_ptr<CJoueur>>& joueurs); // si nécessaire

	void REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPli);
	void REG_AfficherGagnantManche(vector<unique_ptr<CJoueur>>& vJoueurs);
	void REG_AfficherGagnantPartie(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPartie);
	void REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur); // appelle afficherpli
	void REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& mJEU_points);

};
#endif

