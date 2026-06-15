#include "CRegleDameDePique.h"
#include "CPaquet.h"
#include "CJoueur.h"
#include "CCarte.h"
#include "CEquipe.h"
#include "CConsole.h"

bool CRegleDameDePique::REG_SetNbJoueur(unsigned int uiNbJoueurs) {
	// ce jeu peut se jouer à 4 ou 6 joueurs mais ce programme n'implémente que la première
	return (uiNbJoueurs == 4 || uiNbJoueurs==6);
}

// appelle constituer équipe
void CRegleDameDePique::REG_DebutPartie(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points) {
	REG_DistribuerCartes(joueurs, paquet);
	REG_ConstituerEquipes(joueurs, points);
} 


// A FAIRE 
bool CRegleDameDePique::REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& points) { return true; }


unsigned int CRegleDameDePique::REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& point, unsigned int& uiJEU_IdJoueurCourrant) {
	//choisi un premier joueur en aléatoire pour que ce ne soit pas tjs le joueur 0 qui commence
	srand(time(nullptr));
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	unsigned int uiIndicePremierJoueur = rand() % joueurs.size();
	
	// chaque joueur choisi 3 cartes et les donne à un autre joueur. D'après les règles, 1ere manche = donner au joueur de gauche, 
	// 2e manche = joueur d'en face, 3e manche = joueur de droite, 4e manche = pas d'échange et ainsi de suite
	// par soucis de rapidité, ici on donne tt le tps au joueur de droite

	size_t uiIndiceJoueurDeDroite = 0;

	for (size_t i=0; i<joueurs.size(); i++)
	{
		// choisir 3 cartes
		vTroisCartes.push_back(joueurs[i]->JOU_ChoixCarteAJouer());

		while (vTroisCartes[1]->CAR_GetNom() != vTroisCartes[0]->CAR_GetNom()) {
			vTroisCartes.pop_back();
			vTroisCartes.push_back(joueurs[i]->JOU_ChoixCarteAJouer());
		}

		while ((vTroisCartes[2]->CAR_GetNom() != vTroisCartes[0]->CAR_GetNom()) && (vTroisCartes[2]->CAR_GetNom() != vTroisCartes[1]->CAR_GetNom())) {
			vTroisCartes.pop_back();
			vTroisCartes.push_back(joueurs[i]->JOU_ChoixCarteAJouer());
		}

		// les donner au joueur de droite 
		uiIndiceJoueurDeDroite = (i+1)%joueurs.size();
		(joueurs[uiIndiceJoueurDeDroite]->JOU_GetMain())->PAQ_AjouterCarte(move(vTroisCartes[i]));
		(joueurs[uiIndiceJoueurDeDroite]->JOU_GetMain())->PAQ_AjouterCarte(move(vTroisCartes[i]));
		(joueurs[uiIndiceJoueurDeDroite]->JOU_GetMain())->PAQ_AjouterCarte(move(vTroisCartes[i]));
	}

	return uiIndicePremierJoueur;
}


// A FAIRE
bool CRegleDameDePique::REG_ConditionFinManche() { return true; }


void CRegleDameDePique::REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points) {
	for (unsigned int i = 0; i < joueurs.size(); i++) {
		vector<unsigned int> uiNumerosJoueurs;
		uiNumerosJoueurs.push_back(i);

		unique_ptr<CEquipe> pEquipe = make_unique<CEquipe>(uiNumerosJoueurs, i + 1);

		points.emplace(move(pEquipe), 0);
	}
}

// A FAIRE OU A SUPPRIMER ????
void CRegleDameDePique::REG_MettreEnPlacePioche() {}


void CRegleDameDePique::REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet) {
	paquet->PAQ_Melanger();
	for (unsigned int i = 0; i < (paquet->PAQ_GetCartes().size() / joueurs.size()); i++)
	{
		for (unsigned int j = 0; j < joueurs.size(); j++)
		{
			(joueurs[j]->JOU_GetMain())->PAQ_AjouterCarte(paquet->PAQ_RetirerCarte());
		}
	}
	if (paquet->PAQ_GetCartes().size() != 0) {} // erreur
}


bool CRegleDameDePique::REG_PremiereCarte(CCarte& carte) {
	return (carte.CAR_GetCouleur() == "Trefle" && carte.CAR_GetValeur() == 2);
}


bool CRegleDameDePique::REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& pPaquetJoueur) {
	if (bPremiereCarte == true) { 
		bPremiereCarte = false;
		REG_PremiereCarte(carte);
	}
	return true;
}

// appelle à calculer points pli
unsigned int CRegleDameDePique::REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli) { 
	unsigned int uiIndiceJoueurGagnantPli = 0;
	for (unsigned int i = 0; i < vuIdJoueurPli.size(); i++) {

	}
	
	
	return 0;
} 



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