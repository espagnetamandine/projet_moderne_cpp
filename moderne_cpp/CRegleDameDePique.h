#ifndef _CREGLEDAMEDEPIQUE_H
#define _CREGLEDAMEDEPIQUE_H

#include "CRegle.h"
#include <map>

class CRegleDameDePique : public CRegle {
private:

public:
	CRegleDameDePique();
	~CRegleDameDePique();
	
	virtual void REG_DebutPartie(); // appelle constituer équipe
	virtual bool REG_ConditionFinPartie();
	virtual void REG_DebutManche(); // ajouter 1 à la manche
	virtual bool REG_ConditionFinManche();

	virtual void REG_JoueurSuivant(unsigned int uiIndiceJoueur); // n’est jamais appelé directement, change indice joueur courant
	virtual void REG_ConstituerEquipes();
	virtual void REG_MettreEnPlacePioche();


	virtual void REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet> paquet);
	virtual bool REG_PremiereCarte(const CCarte& carte);
	virtual bool REG_CarteValide(const CCarte& carte);

	virtual unsigned int REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli) = 0; // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
	virtual void REG_CalculPointsPli();
	virtual void REG_CalculerPointsManche(); // si nécessaire

	virtual void REG_AfficherGagnantPli(unsigned int uiIndiceJoueurGagnantPli);
	virtual void REG_AfficherGagnantPartie();
	virtual void REG_AfficherMainJoueur(); // appelle afficherpli
	virtual void REG_AfficherPoints();

};
#endif

