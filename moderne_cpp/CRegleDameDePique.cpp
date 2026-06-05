#include "CRegleDameDePique.h"



void CRegleDameDePique::REG_JouerPartie() {
	CCarte carte("Trefle",2); //pas de constructeur par defaut 

	REG_DistribuerCartes();
	while (!REG_FinDePartie()) // partie
	{
		while (!REG_FinDeManche()) // manche
		{
			while (uiREG_IdxJoueurCourrant != vjREG_joueurs.size()) // pli 
			{
				carte = vjREG_joueurs[uiREG_IdxJoueurCourrant].JOUEUR_Choix_Carte_A_Jouer();

				if (uiREG_IdxJoueurCourrant == 0 && !REG_PremiereCarte(carte)) { /* erreur*/ }

				else if (!REG_CarteValide(carte)) { /*erreur*/ }

				else
				{
					mREG_pli[vjREG_joueurs[uiREG_IdxJoueurCourrant]] = carte;
					REG_GagnePli(); //calcule les points 
				}
			}
		}
		REG_AfficherPoints(); // points de la manche 
	}
	REG_AfficherPoints(); // points de la partie
	REG_AfficherGagnant();
}


void CRegleDameDePique::REG_DistribuerCartes() {
	for (unsigned int i = 0; i < (pREG_paquet_de_cartes.PAQ_GetTaille() / vjREG_joueurs.size()); i++) //pas la methode dans CPaquet 
	{
		for (CJoueur joueur : vjREG_joueurs) //CJoueur virtuelle pure
		{
			//joueur.JOUEUR_Choix_Carte_A_Jouer(pREG_paquet_de_cartes[i]);
		}
	}
}


bool CRegleDameDePique::REG_PremiereCarte(CCarte carte) {
	return (carte.getCAR_couleur() == "Trefle" && carte.getCAR_valeur() == 2);
}


bool CRegleDameDePique::REG_CarteValide(CCarte carte) {
	return true;
}


bool EstDansVecteur(vector<int> v, int numero) {
	for (int i : v) {
		if (numero == i)
			return true;
	}
	return false;
}

void CRegleDameDePique::REG_AfficherPoints() {
	for (int i = 0; i < vjREG_joueurs.size(); i++) {
		auto itEquipe = vjREG_equipes.find(vjREG_joueurs[i]);
		auto itPoints = vjREG_points.find(vjREG_joueurs[i]);
		if(itPoints == vjREG_points.end()) { /*erreur*/ }
		else if (itEquipe != vjREG_equipes.end()) {
			cout << "Equipe " << itEquipe->second.EQU_GetNumero() << " : " << itPoints->second << endl;
		}
		else { /* erreur */ }
	}
}


void CRegleDameDePique::REG_AfficherGagnant() {
	CJoueur jJoueurMax = vjREG_joueurs[0]; // CJoueur classe abstraite
	int iPointsMax = 0;
	for (auto it = vjREG_points.begin(); it != vjREG_points.end(); ++it)
	{
		if (it->second > iPointsMax)
		{
			iPointsMax = it->second;
			jJoueurMax = it->first;
		}
	}
	auto itEquipe = vjREG_equipes.find(jJoueurMax);
	if (itEquipe == vjREG_equipes.end()) { /* erreur */ }
	
	cout << "L'équipe gagnant est : " << itEquipe->second << " avec " << iPointsMax << " Points." << endl;

	cout << "Félicitation ";
	// pas encore repri la boucle for
	/*for (CJoueur j : vjREG_joueurs)
	{
		if (j.JOU_GetEquipe() == jJoueurMax.JOU_GetEquipe)
		{
			cout << j.JOU_GetName();
		}
	}*/
	cout << endl;
}