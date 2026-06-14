
#include "CRegleDameDePique.h"
#include "CEquipe.h"

void CRegleDameDePique::REG_DebutPartie() {} // appelle constituer équipe
bool CRegleDameDePique::REG_ConditionFinPartie() { return true; }
void CRegleDameDePique::REG_DebutManche() {} // ajouter 1 à la manche
bool CRegleDameDePique::REG_ConditionFinManche() { return true; }

void CRegleDameDePique::REG_JoueurSuivant(unsigned int uiIndiceJoueur) {} // n’est jamais appelé directement, change indice joueur courant
void CRegleDameDePique::REG_ConstituerEquipes() {}
void CRegleDameDePique::REG_MettreEnPlacePioche() {}




void CRegleDameDePique::REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet) {
	for (unsigned int i = 0; i < (paquet->PAQ_GetCartes().size() / joueurs.size()); i++)
	{
		for (unsigned int j = 0; j < joueurs.size(); j++)
		{
			(joueurs[j]->JOU_GetMain())->PAQ_AjouterCarte(paquet->PAQ_RetirerCarte());
		}
	}
}


bool CRegleDameDePique::REG_PremiereCarte(CCarte& carte) {
	return (carte.CAR_GetCouleur() == "Trefle" && carte.CAR_GetValeur() == 2);
}


bool CRegleDameDePique::REG_CarteValide(CCarte& carte) {
	return true;
}




unsigned int CRegleDameDePique::REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli) { return 0; } // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
void CRegleDameDePique::REG_CalculerPointsPli() {}
void CRegleDameDePique::REG_CalculerPointsManche() {} // si nécessaire


void CRegleDameDePique::REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPli) {
	cout << vJoueurs[uiIndiceJoueurGagnantPli]->JOU_GetNomJoueur() << " remporte le pli." << endl;
}


void CRegleDameDePique::REG_AfficherGagnantPartie(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPartie) {
	cout << "Félicitations " << vJoueurs[uiIndiceJoueurGagnantPartie]->JOU_GetNomJoueur() << " vous avez gagné !" << endl;
}


void CRegleDameDePique::REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur) {
	pJoueur->JOU_GetMain()->PAQ_Afficher();
}


bool EstDansVecteur(vector<int> v, int numero) {
	for (int i : v) {
		if (numero == i)
			return true;
	}
	return false;
}

void CRegleDameDePique::REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& mJEU_points) {
	for (auto it = mJEU_points.begin(); it != mJEU_points.end(); ++it)
	{
		cout << it->first->getEQU_numeroEquipe() << " : " << it->second << endl;
	}
}