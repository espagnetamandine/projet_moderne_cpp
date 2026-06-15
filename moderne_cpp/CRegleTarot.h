#ifndef _CREGLETAROT_H
#define _CREGLETAROT_H

#include "CRegle.h"
#include <map>

class CRegleTarot : public CRegle {
private:
	unique_ptr<CPaquet> pREG_Chien;
public:
	CRegleTarot()= default;
	~CRegleTarot()= default;
	

	bool REG_SetNbJoueur(unsigned int uiNbJoueurs);

	void REG_DebutPartie(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points); // appelle constituer équipe
	bool REG_ConditionFinPartie();
	unsigned int REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int& uiJEU_IdJoueurCourrant); // ajouter 1 à la manche
	bool REG_ConditionFinManche(vector<unique_ptr<CJoueur>>& joueurs);

	
	void REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points);
	void REG_MettreEnPlacePioche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs);


	void REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet);

	bool REG_PremiereCarte(CCarte& carte);

	bool REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& pPaquetJoueur);

	unsigned int REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli); // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
	void REG_CalculerPointsPli();
	void REG_CalculerPointsManche(); // si nécessaire

	void REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPli);
	void REG_AfficherGagnantPartie(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPartie);
	void REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur); // appelle afficherpli
	void REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& mJEU_points);

};
#endif

