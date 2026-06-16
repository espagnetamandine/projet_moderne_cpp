#include "CRegleTarot.h"
#include "CPaquet.h"
#include "CJoueur.h"
#include "CCarte.h"
#include "CEquipe.h"
#include "CConsole.h"


bool CRegleTarot::REG_SetNbJoueur(unsigned int uiNbJoueurs){}

void CRegleTarot::REG_DebutPartie(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points) {} // appelle constituer équipe
bool  CRegleTarot::REG_ConditionFinPartie(){}

unsigned int CRegleTarot::REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int& uiJEU_IdJoueurCourrant) 
{
	paquet->PAQ_Melanger();
	REG_MettreEnPlacePioche(paquet, joueurs);
	REG_DistribuerCartes(joueurs, paquet);
	return (uiJEU_IdJoueurCourrant + 1)% joueurs.size();

} 
bool  CRegleTarot::REG_ConditionFinManche(vector<unique_ptr<CJoueur>>& joueurs)
{
	if (joueurs[0]->JOU_GetMain()->PAQ_GetCartes().size() == 0)
	{
		return true;
	}
	return false;
}

void CRegleTarot::REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points){}

void CRegleTarot::REG_MettreEnPlacePioche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs)
{
	pREG_Chien = CPaquetManager::PAQ_CreerPaquet("Joueur");
	unsigned int uiNbCartesChien = 0;
	if (joueurs.size() == 5)
	{
		uiNbCartesChien = 3;
	}
	else
	{
		uiNbCartesChien = 6;
	}
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbCartesChien; uiBoucle++)
	{
		unique_ptr<CCarte> carte = paquet->PAQ_RetirerCarte();
		pREG_Chien->PAQ_AjouterCarte(move(carte));
	}

}




void CRegleTarot:: REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet) 
{
	
	
	for (unsigned int uiBoucle = 0; uiBoucle < (((paquet->PAQ_GetCartes().size()) / joueurs.size())/3); uiBoucle++) //pas la methode dans CPaquet 
	{
		for (auto& joueur: joueurs) //CJoueur virtuelle pure
		{
			for (unsigned int uiBoucle2 = 0; uiBoucle2 < 3; uiBoucle2++)
			{
				unique_ptr<CCarte> carte = paquet->PAQ_RetirerCarte();
				joueur->JOU_GetMain()->PAQ_AjouterCarte(move(carte));
			}
			
		}
	}
}


bool CRegleTarot::REG_PremiereCarte(CCarte& carte) {
	return true;
}

bool CRegleTarot::REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& pPaquetJoueur)  // 
{
	return true;
}


bool EstDansVecteur(vector<int> v, int numero) {
	for (int i : v) {
		if (numero == i)
			return true;
	}
	return false;
}




unsigned int CRegleTarot::REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli) {}// appelle à joueur suivant + calculer points pli + ajouter 1 au pli
void CRegleTarot::REG_CalculerPointsPli(){}
void CRegleTarot::REG_CalculerPointsManche() {} // si nécessairewini

void CRegleTarot::REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>&vJoueurs, unsigned int uiIndiceJoueurGagnantPli){}
void CRegleTarot::REG_AfficherGagnantPartie(vector<unique_ptr<CJoueur>>&vJoueurs, unsigned int uiIndiceJoueurGagnantPartie){}
void CRegleTarot::REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur) {} // appelle afficherpli
void CRegleTarot::REG_AfficherPoints(map<unique_ptr<CEquipe>, int>&mJEU_points){}