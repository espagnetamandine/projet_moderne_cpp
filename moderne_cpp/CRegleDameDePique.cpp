
#include "CRegleDameDePique.h"
#include "CEquipe.h"


void CRegleDameDePique::REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet) {
	for (unsigned int i = 0; i < (paquet->getPAQ_Cartes().size() / joueurs.size()); i++)
	{
		for (unsigned int j = 0; j < joueurs.size(); j++)
		{
			(joueurs[j]->getJOU_main())->PAQ_AjouterCarte(paquet->PAQ_RetirerCarte());
		}
	}
}


bool CRegleDameDePique::REG_PremiereCarte(CCarte& carte) {
	return (carte.CAR_GetCouleur() == "Trefle" && carte.CAR_GetValeur() == 2);
}


bool CRegleDameDePique::REG_CarteValide(CCarte& carte) {
	return true;
}


void CRegleDameDePique::REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPli) {
	cout << vJoueurs[uiIndiceJoueurGagnantPli]->getJOU_nomJoueur() << " remporte le pli." << endl;
}


void CRegleDameDePique::REG_AfficherGagnantPartie(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPartie) {
	cout << "Félicitations " << vJoueurs[uiIndiceJoueurGagnantPartie]->getJOU_nomJoueur() << " vous avez gagné !" << endl;
}


void CRegleDameDePique::REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur) {
	pJoueur->getJOU_main()->PAQ_Afficher();
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