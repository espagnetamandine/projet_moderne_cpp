#include "CRegleDameDePique.h"


void CRegleDameDePique::REG_DistribuerCartes(CJeu<CRegle>& jeu) {
	CPaquet paquet = jeu.JEU_GetPaquet();
	vector<CJoueur> joueurs = jeu.JEU_GetJoueurs();
	for (unsigned int i = 0; i < (paquet.PAQ_GetTaille() / joueurs.size()); i++)
	{
		for (CJoueur j : joueurs)
		{
			j.JOU_AjouterCarteMain(paquet[i]);
		}
	}
}

bool CRegleDameDePique::REG_PremiereCarte(CCarte carte) {
	return (carte.CAR_GetCouleur() == "Trefle" && carte.CAR_GetValeur() == 2);
}

bool CRegleDameDePique::REG_CarteValide() {
	return true;
}
