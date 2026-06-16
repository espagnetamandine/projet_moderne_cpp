#include "CRegleDameDePique.h"
#include "CPaquet.h"
#include "CJoueur.h"
#include "CCarte.h"
#include "CEquipe.h"
#include "CConsole.h"

#include <stdio.h>
using namespace std;

/********************************************************/
/*                  SETTERS ET GETTERS                  */
/********************************************************/

bool CRegleDameDePique::REG_VerificationNbJoueur(unsigned int uiNbJoueurs) {
	// ce jeu peut se jouer à 4 ou 6 joueurs mais ce programme n'implémente que la première
	return (uiNbJoueurs == 4 || uiNbJoueurs==6);
}


/********************************************************/
/*                  METHODES DE CREGLE                  */
/********************************************************/

void CRegleDameDePique::REG_DebutPartie(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points) {
	REG_ConstituerEquipes(joueurs, points);
} 


bool CRegleDameDePique::REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& points) {
	int iScoreEquipe;
	for (auto it = points.begin(); it != points.end(); ++it)
	{
		iScoreEquipe = it->second;

		if (iScoreEquipe >= 100) // ce score pourrait être parametrable 
		{
			cout << "\n[DAME DE PIQUE] Fin de la partie ! L'equipe "
				<< it->first->getEQU_numeroEquipe()
				<< " a depasse les 100 points (" << iScoreEquipe << " pts) !" << endl;
			return true;
		}
	}
	return false;
}


// chaque joueur choisi 3 cartes et les donne à un autre joueur. D'après les règles, 1ere manche = donner au joueur de gauche, 
// 2e manche = joueur d'en face, 3e manche = joueur de droite, 4e manche = pas d'échange et ainsi de suite.
// Par soucis de rapidité, ici on donne tout le temps au joueur de droite
unsigned int CRegleDameDePique::REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int& uiJEU_IdJoueurCourrant) {
	cout << "Une fois pret a lancer la manche, veuillez presser ENTREE pour continuer.\n";

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	CConsole::COS_NettoyerEcran();

	/*-----------------------
	|  DEBUT DE LA MANCHE   |
	-----------------------*/

	// distribution
	REG_DistribuerCartes(joueurs, paquet);

	// chaque joueur doit choisir 3 cartes
	size_t uiIndiceJoueurDeDroite = 0;
	for (size_t i = 0; i < joueurs.size(); i++)
	{
		// on récupère le score par équipe (ie par joueur) pour l'appel à la méthode de CConsole
		vector<unsigned int> vScoreEquipe;
		for (auto it = points.begin(); it != points.end(); ++it)
		{
			vScoreEquipe.push_back(it->second);
		}

		
		// 1. Affichage secret
		CConsole::COS_AfficherEcranSecretJoueur(
			joueurs[i],
			i,
			vScoreEquipe[i]
		);

		cout << " Choisissez 3 cartes de votre main afin de les passer au joueur de droite. " << endl;
		
		cout << "Choix première carte : ";
		vTroisCartes.push_back(joueurs[i]->JOU_ChoixCarteAJouer());

		joueurs[i]->JOU_GetMain()->PAQ_AfficherAvecIdentifiant();
		cout << "Choix deuxième carte : ";
		vTroisCartes.push_back(joueurs[i]->JOU_ChoixCarteAJouer());

		joueurs[i]->JOU_GetMain()->PAQ_AfficherAvecIdentifiant();
		cout << "Choix troisième carte : ";
		vTroisCartes.push_back(joueurs[i]->JOU_ChoixCarteAJouer());

		if (vTroisCartes[1] == vTroisCartes[0] || vTroisCartes[2] == vTroisCartes[0] || vTroisCartes[2] == vTroisCartes[1]) {} // erreur 
	}

	// puis donner les trois cartes au joueur de droite 
	for (size_t i = 0; i < joueurs.size(); i++)
	{
		uiIndiceJoueurDeDroite = (i+1)%joueurs.size();
		(joueurs[uiIndiceJoueurDeDroite]->JOU_GetMain())->PAQ_AjouterCarte(move(vTroisCartes[i]));
		(joueurs[uiIndiceJoueurDeDroite]->JOU_GetMain())->PAQ_AjouterCarte(move(vTroisCartes[i]));
		(joueurs[uiIndiceJoueurDeDroite]->JOU_GetMain())->PAQ_AjouterCarte(move(vTroisCartes[i]));
	}
	while (!vTroisCartes.empty()) { vTroisCartes.pop_back(); }

	CConsole::COS_NettoyerEcran();	
	cout << "**************************************************" << endl;
	cout << "               DEBUT DE LA MANCHE                 " << endl;
	cout << "**************************************************" << endl;

	cout << "\nLa manche peut commencer !" << endl;
	cout << "\nAppuyez sur ENTREE des que vous etes pret a demarrer.";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	CConsole::COS_NettoyerEcran();

	// on choisit un premier joueur en aléatoire pour que ce ne soit pas toujours le joueur 0 qui commence
	srand(time(nullptr));
	unsigned int uiIndicePremierJoueur = rand() % joueurs.size();
	cout << "Le premier joueur est " << joueurs[uiIndicePremierJoueur]->JOU_GetNomJoueur() << endl;
	return uiIndicePremierJoueur;
}


bool CRegleDameDePique::REG_ConditionFinManche(const vector<unique_ptr<CJoueur>>& joueurs) {
	for (unsigned int i = 0; i < joueurs.size(); i++) {
		if (!joueurs[i]->JOU_GetMain()->PAQ_GetCartes().empty()) { return false; }
	}
	cout << "La manche est terminée." << endl;
	return true; 
}


void CRegleDameDePique::REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points) {
	// pas besoin d'afficher les équipes car ce jeu ne se joue pas en équipe
	for (unsigned int i = 0; i < joueurs.size(); i++) {
		vector<unsigned int> uiNumerosJoueurs;
		uiNumerosJoueurs.push_back(i);

		unique_ptr<CEquipe> pEquipe = make_unique<CEquipe>(uiNumerosJoueurs, i + 1);

		points.emplace(move(pEquipe), 0);
	}
}


// A SUPPRIMER ?????
void CRegleDameDePique::REG_MettreEnPlacePioche() {};


void CRegleDameDePique::REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet) {
	paquet->PAQ_Melanger();
	
	// vider la main de chaque joueur au cas où elle contiendrait des cartes 
	for (unsigned int k = 0; k < joueurs.size(); k++)
	{
		(joueurs[k]->JOU_GetMain())->PAQ_GetCartes().clear();
	}
	
	for (unsigned int i = 0; i < (paquet->PAQ_GetCartes().size() / joueurs.size()); i++)
	{
		for (unsigned int j = 0; j < joueurs.size(); j++)
		{
			(joueurs[j]->JOU_GetMain())->PAQ_AjouterCarte(paquet->PAQ_RetirerCarte());
		}
	}
	if (paquet->PAQ_GetCartes().size() != 0) {} // erreur

	cout << "[DAME DE PIQUE] Distribution terminee. Tous les joueurs ont 13 cartes." << endl;
}


bool CRegleDameDePique::REG_PremiereCarte(CCarte& carte) {
	return (carte.CAR_GetCouleur() == "Trefle" && carte.CAR_GetValeur() == 2);
}


bool CRegleDameDePique::REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& pPaquetJoueur, const unique_ptr<CPaquet>& pPli, const vector<unsigned int>& vuIdJoueurPli){
	if (bPremiereCarte == true) { 
		bPremiereCarte = false;
		REG_PremiereCarte(carte);
	}
	return true;
}

unsigned int CRegleDameDePique::REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli) {
	string sCouleur;
	unsigned int uiValeur;
	string sCouleurGagnant = pPli->PAQ_GetCartes()[0]->CAR_GetCouleur();
	unsigned int uiValeurGagnant = pPli->PAQ_GetCartes()[0]->CAR_GetValeur();
	unsigned int uiIndiceJoueurGagnantPli = 0;
	for (unsigned int i = 1; i < vuIdJoueurPli.size(); i++) {
		sCouleur = pPli->PAQ_GetCartes()[i]->CAR_GetCouleur();
		uiValeur = pPli->PAQ_GetCartes()[i]->CAR_GetValeur();
		if (sCouleur == sCouleurGagnant && uiValeur > uiValeurGagnant)
		{
			uiValeurGagnant = uiValeur;
			uiIndiceJoueurGagnantPli = i;
		}
	}
	return uiIndiceJoueurGagnantPli;
}



void CRegleDameDePique::REG_CalculerPointsPli(unique_ptr<CPaquet>& pPli, unsigned int uiIndiceJoueurGagnantPli, map<unique_ptr<CEquipe>, int>& points, unique_ptr<CPaquet>& pDefausse) {
	unsigned int uiPointsAAjouter = 0;
	for (unique_ptr<CCarte>& carte : pPli->PAQ_GetCartes()) {
		if (carte->CAR_GetCouleur() == "Coeur") { uiPointsAAjouter++; }
		if (carte->CAR_GetCouleur() == "Pique" && carte->CAR_GetValeur() == 12) { uiPointsAAjouter+=13; }
	}
	for (auto it = points.begin(); it != points.end(); ++it) {
		if (it->first->getEQU_numeroEquipe() == uiIndiceJoueurGagnantPli) {
			it->second += uiPointsAAjouter;
		}
	}
}


void CRegleDameDePique::REG_CalculerPointsManche(unique_ptr<CPaquet>& pPli, unsigned int uiIndiceJoueurGagnantPli, map<unique_ptr<CEquipe>, int>& points, unique_ptr<CPaquet>& pDefausse, const vector<unique_ptr<CJoueur>>& joueurs) {} // pas nécessaire pour ce jeu

void CRegleDameDePique::REG_RemettreCartesDansPaquet(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet) {
	for (unique_ptr<CJoueur>& joueur : joueurs) {
		vector<unique_ptr<CCarte>>& mainJoueur = joueur->JOU_GetMain()->PAQ_GetCartes();

		while (!mainJoueur.empty()) {
			paquet->PAQ_AjouterCarte(move(mainJoueur.back()));
			mainJoueur.pop_back();
		}
	}
}


/********************************************************/
/*                 METHODES SPECIALISEES                */
/********************************************************/



/********************************************************/
/*                       AFFICHAGE                      */
/********************************************************/

void CRegleDameDePique::REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPli) {
	cout << vJoueurs[uiIndiceJoueurGagnantPli]->JOU_GetNomJoueur() << " remporte le pli." << endl;
}


void CRegleDameDePique::REG_AfficherGagnantPartie(map<unique_ptr<CEquipe>, int>& points, const vector<unique_ptr<CJoueur>>& joueurs) {
	//cout << "Félicitations " << vJoueurs[uiIndiceJoueurGagnantPartie]->JOU_GetNomJoueur() << " vous avez gagné !" << endl;
}


void CRegleDameDePique::REG_AfficherMainJoueur(unsigned int uiIdJoueur, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points) {
	//pJoueur->JOU_GetMain()->PAQ_Afficher();
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