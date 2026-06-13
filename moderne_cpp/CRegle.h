#ifndef _CREGLE_H
#define _CREGLE_H

#include "CCarte.h"
#include "CPaquet.h"
#include "CJoueur.h"

#include <vector>
#include <map>

class CRegle {
public:
	CRegle();
	~CRegle();
	
	virtual void REG_DebutPartie() = 0; // appelle constituer équipe
	virtual bool REG_ConditionFinPartie() = 0;
	virtual void REG_DebutManche() = 0; // ajouter 1 à la manche
	virtual bool REG_ConditionFinManche() = 0;

	virtual void REG_JoueurSuivant(unsigned int uiIndiceJoueur) = 0; // n’est jamais appelé directement, change indice joueur courant
	virtual void REG_ConstituerEquipes() = 0;
	virtual void REG_MettreEnPlacePioche() = 0;


	virtual void REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet> paquet) = 0;
	virtual bool REG_PremiereCarte(const CCarte& carte) = 0;
	virtual bool REG_CarteValide(const CCarte& carte) = 0;
	
	virtual unsigned int REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli) = 0; // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
	virtual void REG_CalculPointsPli() = 0;
	virtual void REG_CalculerPointsManche() = 0; // si nécessaire

	virtual void REG_AfficherGagnantPli(unsigned int uiIndiceJoueurGagnantPli) = 0;
	virtual void REG_AfficherGagnantPartie() = 0;
	virtual void REG_AfficherMainJoueur() = 0; // appelle afficherpli
	virtual void REG_AfficherPoints() = 0;

};




#endif 
