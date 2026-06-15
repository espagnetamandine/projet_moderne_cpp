#ifndef _CREGLEBelote_H
#define _CREGLEBelote_H

#include "CRegle.h"
#include <map>

class CRegleBelote : public CRegle {
private:

public:

	virtual bool REG_SetNbJoueur(unsigned int uiNbJoueurs);

	// FIN PLUS
public:
	CRegleBelote() = default;
	~CRegleBelote() = default;

	virtual void REG_DebutPartie(
		unique_ptr<CPaquet>& paquet,
		vector<unique_ptr<CJoueur>>& joueurs,
		map<unique_ptr<CEquipe>, int>& points
	);

	virtual bool REG_ConditionFinPartie();
	virtual void REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& point); // ajouter 1 à la manche
	virtual bool REG_ConditionFinManche();

	virtual void REG_JoueurSuivant(unsigned int uiIndiceJoueur); // n’est jamais appelé directement, change indice joueur courant
	virtual void REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points);
	virtual void REG_MettreEnPlacePioche();

	virtual void REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet);
	virtual bool REG_PremiereCarte(CCarte& carte);
	virtual bool REG_CarteValide(CCarte& carte);

	virtual unsigned int REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli); // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
	virtual void REG_CalculerPointsPli();
	virtual void REG_CalculerPointsManche(); // si nécessaire

	virtual void REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPli);
	virtual void REG_AfficherGagnantPartie(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPartie);
	virtual void REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur); // appelle afficherpli
	virtual void REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& mJEU_points);

};
#endif

