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

public:
	CRegleTarot();
	~CRegleTarot();

	 void REG_DebutPartie();
	 bool REG_ConditionFinPartie();
	 void REG_DebutManche();
	 bool REG_ConditionFinManche();
	 void REG_JoueurSuivant(unsigned int uiIndiceJueur);
	 void REG_ConstituerEquipes();
	 void REG_MettreEnPlacePioche();
	 void REG_Distribuer();
	 unsigned int REG_DeterminerIndiceGagnantPli();
	 bool REG_CarteValide();
	 void REG_CalculerPointsPli();
	 void REG_CalculerPointsManche();
	 void REG_AfficherGagnantPli();
	 void REG_AfficherGagnantPartie();
	 void REG_AfficherMainJoueur();
	 void REG_AfficherPoints();
};
#endif

