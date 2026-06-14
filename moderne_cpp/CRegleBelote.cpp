#include "CRegleBelote.h"

bool CRegleBelote::REG_SetNbJoueur(unsigned int uiNbJoueurs)
{
	if (uiNbJoueurs == 3 || uiNbJoueurs == 4)
	{
		uiNbJoueurPossible = uiNbJoueurs;
		return true;
	}

	return false;
}

void CRegleBelote::REG_DebutPartie() {}; // appelle constituer équipe
bool CRegleBelote::REG_ConditionFinPartie() { return true; };
void CRegleBelote::REG_DebutManche() {}; // ajouter 1 à la manche
bool CRegleBelote::REG_ConditionFinManche() { return true; };

void CRegleBelote::REG_JoueurSuivant(unsigned int uiIndiceJoueur) {}; // n’est jamais appelé directement, change indice joueur courant
void CRegleBelote::REG_ConstituerEquipes() {};
void CRegleBelote::REG_MettreEnPlacePioche() {};

void CRegleBelote::REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet) {};
bool CRegleBelote::REG_PremiereCarte(CCarte& carte) { return true; };
bool CRegleBelote::REG_CarteValide(CCarte& carte) { return true; };

unsigned int CRegleBelote::REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli) { return 1; }; // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
void CRegleBelote::REG_CalculerPointsPli() {};
void CRegleBelote::REG_CalculerPointsManche() {}; // si nécessaire

void CRegleBelote::REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPli) {};
void CRegleBelote::REG_AfficherGagnantPartie(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPartie) {};
void CRegleBelote::REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur) {}; // appelle afficherpli
void CRegleBelote::REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& mJEU_points) {};


