#include "CRegleDameDePique.h"
#include "CPaquet.h"
#include "CJoueur.h"
#include "CCarte.h"
#include "CEquipe.h"
#include "CConsole.h"

#include <stdio.h>

using namespace std;

/********************************************************/
/*                    METHODES DE JEU                   */
/********************************************************/

void CRegleDameDePique::REG_DebutPartie(unique_ptr<CPaquet>& upPaquetPrincipal, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe) {
	REG_ConstituerEquipes(vuJoueurs, muPointsEquipe);
} 


bool CRegleDameDePique::REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& muPointsEquipe) {
	int iScoreEquipe;
	for (auto it = muPointsEquipe.begin(); it != muPointsEquipe.end(); ++it)
	{
		iScoreEquipe = it->second;

		if (iScoreEquipe >= 100) // ce score pourrait être parametrable 
		{
			return true;
		}
	}
	return false;
}


// chaque joueur choisi 3 cartes et les donne à un autre joueur. D'après les règles, 1ere manche = donner au joueur de gauche, 
// 2e manche = joueur d'en face, 3e manche = joueur de droite, 4e manche = pas d'échange et ainsi de suite.
// Par soucis de rapidité, ici on donne tout le temps au joueur de droite
unsigned int CRegleDameDePique::REG_DebutManche(unique_ptr<CPaquet>& upPaquetPrincipal, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unsigned int& uiIdJoueurCourrant) {
	cout << "Une fois pret a lancer la manche, veuillez presser ENTREE pour continuer.\n";

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	CConsole::COS_NettoyerEcran();

	/*-----------------------
	|  DEBUT DE LA MANCHE   |
	-----------------------*/

	// distribution
	REG_DistribuerCartes(vuJoueurs, upPaquetPrincipal);

	// chaque joueur doit choisir 3 cartes
	size_t uiIndiceJoueurDeDroite = 0;
	for (size_t i = 0; i < vuJoueurs.size(); i++)
	{
		// on récupère le score par équipe (ie par joueur) pour l'appel à la méthode de CConsole
		vector<unsigned int> vScoreEquipe;
		for (auto it = muPointsEquipe.begin(); it != muPointsEquipe.end(); ++it)
		{
			vScoreEquipe.push_back(it->second);
		}

		
		// 1. Affichage secret
		CConsole::COS_AfficherEcranSecretJoueur(
			vuJoueurs[i],
			i,
			vScoreEquipe[i]
		);

		cout << " Choisissez 3 cartes de votre main afin de les passer au joueur de droite. " << endl;
		
		//cout << "Choix première carte : ";
		//vTroisCartes.push_back(vuJoueurs[i]->JOU_ChoixCarteAJouer());

		//vuJoueurs[i]->JOU_GetMain()->PAQ_AfficherAvecIdentifiant();
		//cout << "Choix deuxième carte : ";
		//vTroisCartes.push_back(vuJoueurs[i]->JOU_ChoixCarteAJouer());

		//vuJoueurs[i]->JOU_GetMain()->PAQ_AfficherAvecIdentifiant();
		//cout << "Choix troisième carte : ";
		//vTroisCartes.push_back(vuJoueurs[i]->JOU_ChoixCarteAJouer());

		if (vTroisCartes[1] == vTroisCartes[0] || vTroisCartes[2] == vTroisCartes[0] || vTroisCartes[2] == vTroisCartes[1]) {} // erreur 
	}

	// puis donner les trois cartes au joueur de droite 
	for (size_t i = 0; i < vuJoueurs.size(); i++)
	{
		uiIndiceJoueurDeDroite = (i+1)% vuJoueurs.size();
		(vuJoueurs[uiIndiceJoueurDeDroite]->JOU_GetMain())->PAQ_AjouterCarte(move(vTroisCartes[i]));
		(vuJoueurs[uiIndiceJoueurDeDroite]->JOU_GetMain())->PAQ_AjouterCarte(move(vTroisCartes[i]));
		(vuJoueurs[uiIndiceJoueurDeDroite]->JOU_GetMain())->PAQ_AjouterCarte(move(vTroisCartes[i]));
	}
	while (!vTroisCartes.empty()) { vTroisCartes.pop_back(); }

	CConsole::COS_NettoyerEcran();

	cout << "--------------------------------------------------" << endl;
	cout << "               Debut de la manche                 " << endl;
	cout << "--------------------------------------------------" << endl;

	cout << "\nLa manche peut commencer !" << endl;
	cout << "\nAppuyez sur ENTREE des que vous etes pret a demarrer.";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	CConsole::COS_NettoyerEcran();

	// on choisit un premier joueur en aléatoire pour que ce ne soit pas toujours le joueur 0 qui commence
	srand(time(nullptr));
	unsigned int uiIndicePremierJoueur = rand() % vuJoueurs.size();
	cout << "Le premier joueur est " << vuJoueurs[uiIndicePremierJoueur]->JOU_GetNomJoueur() << endl;
	return uiIndicePremierJoueur;
}


bool CRegleDameDePique::REG_ConditionFinManche(const vector<unique_ptr<CJoueur>>& vuJoueurs) {
	for (unsigned int i = 0; i < vuJoueurs.size(); i++) {
		if (!vuJoueurs[i]->JOU_GetMain()->PAQ_GetCartes().empty()) { return false; }
	}
	cout << "La manche est terminée." << endl;
	return true; 
}

bool CRegleDameDePique::REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& pPaquetJoueur, const unique_ptr<CPaquet>& pPli, const vector<unsigned int>& vuIdJoueurPli) {
	if (bPremiereCarte == true) {
		bPremiereCarte = false;
		REG_PremiereCarte(carte);
	}
	return true;
}

/********************************************************/
/*                     ENTRE - JEU                      */
/********************************************************/

unsigned int CRegleDameDePique::REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& upPli, vector<unsigned int>& vuIdJoueurPli) {
	string sCouleur;
	unsigned int uiValeur;
	string sCouleurGagnant = upPli->PAQ_GetCartes()[0]->CAR_GetCouleur();
	unsigned int uiValeurGagnant = upPli->PAQ_GetCartes()[0]->CAR_GetValeur();
	unsigned int uiIndiceJoueurGagnantPli = 0;

	for (unsigned int i = 1; i < vuIdJoueurPli.size(); i++) {
		sCouleur = upPli->PAQ_GetCartes()[i]->CAR_GetCouleur();
		uiValeur = upPli->PAQ_GetCartes()[i]->CAR_GetValeur();
		if (sCouleur == sCouleurGagnant && uiValeur > uiValeurGagnant)
		{
			uiValeurGagnant = uiValeur;
			uiIndiceJoueurGagnantPli = i;
		}
	}
	return uiIndiceJoueurGagnantPli;
}


void CRegleDameDePique::REG_CalculerPointsPli(unique_ptr<CPaquet>& upPli, unsigned int uiIndiceJoueurGagnantPli, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unique_ptr<CPaquet>& upDefausse) {
	unsigned int uiPointsAAjouter = 0;
	for (unique_ptr<CCarte>& carte : upPli->PAQ_GetCartes()) {
		if (carte->CAR_GetCouleur() == "Coeur") { uiPointsAAjouter++; }
		if (carte->CAR_GetCouleur() == "Pique" && carte->CAR_GetValeur() == 12) { uiPointsAAjouter += 13; }
	}
	for (auto it = muPointsEquipe.begin(); it != muPointsEquipe.end(); ++it) {
		if (it->first->getEQU_numeroEquipe() == uiIndiceJoueurGagnantPli) {
			it->second += uiPointsAAjouter;
		}
	}
}

/********************************************************/
/*                    MISES EN PLACE                    */
/********************************************************/

bool CRegleDameDePique::REG_VerificationNbJoueur(unsigned int uiNbJoueurs) {
	// Ce jeu peut se jouer à 4 ou 6 joueurs mais ce programme n'implémente que le fait de jouer à 4.
	return (uiNbJoueurs == 4 || uiNbJoueurs == 6);
}

void CRegleDameDePique::REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unsigned int uiIndincePreneur) {
	// pas besoin d'afficher les équipes car ce jeu ne se joue pas en équipe
	for (unsigned int i = 0; i < vuJoueurs.size(); i++) {
		vector<unsigned int> uiNumerosJoueurs;
		uiNumerosJoueurs.push_back(i);

		unique_ptr<CEquipe> pEquipe = make_unique<CEquipe>(uiNumerosJoueurs, i + 1);

		muPointsEquipe.emplace(move(pEquipe), 0);
	}
}

void CRegleDameDePique::REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& vuJoueurs, unique_ptr<CPaquet>& upPaquetPrincipal) {
	upPaquetPrincipal->PAQ_Melanger();

	// vider la main de chaque joueur au cas où elle contiendrait des cartes 
	for (unsigned int k = 0; k < vuJoueurs.size(); k++)
	{
		(vuJoueurs[k]->JOU_GetMain())->PAQ_GetCartes().clear();
	}

	for (unsigned int i = 0; i < (upPaquetPrincipal->PAQ_GetCartes().size() / vuJoueurs.size()); i++)
	{
		for (unsigned int j = 0; j < vuJoueurs.size(); j++)
		{
			(vuJoueurs[j]->JOU_GetMain())->PAQ_AjouterCarte(upPaquetPrincipal->PAQ_RetirerCarte());
		}
	}
	if (upPaquetPrincipal->PAQ_GetCartes().size() != 0) {} // erreur

	cout << "Distribution terminee. Tous les joueurs ont 13 cartes." << endl;
}



void CRegleDameDePique::REG_RemettreCartesDansPaquet(vector<unique_ptr<CJoueur>>& vuJoueurs, unique_ptr<CPaquet>& upPaquetPrincipal) {
	for (unique_ptr<CJoueur>& joueur : vuJoueurs) {
		vector<unique_ptr<CCarte>>& mainJoueur = joueur->JOU_GetMain()->PAQ_GetCartes();

		while (!mainJoueur.empty()) {
			upPaquetPrincipal->PAQ_AjouterCarte(move(mainJoueur.back()));
			mainJoueur.pop_back();
		}
	}
}

/********************************************************/
/*                 METHODES SPECIALISEES                */
/********************************************************/

bool CRegleDameDePique::REG_PremiereCarte(CCarte& pcCarte) {
	return (pcCarte.CAR_GetCouleur() == "Trefle" && pcCarte.CAR_GetValeur() == 2);
}

/********************************************************/
/*                       AFFICHAGE                      */
/********************************************************/

void CRegleDameDePique::REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vuJoueurs, unsigned int uiIndiceJoueurGagnantPli) {
	cout << vuJoueurs[uiIndiceJoueurGagnantPli]->JOU_GetNomJoueur() << " remporte le pli." << endl;
}

void CRegleDameDePique::REG_AfficherGagnantManche(map<unique_ptr<CEquipe>, int>& muPointsEquipe, const vector<unique_ptr<CJoueur>>& vuJoueurs)
{
}

void CRegleDameDePique::REG_AfficherGagnantPartie(map<unique_ptr<CEquipe>, int>& muPointsEquipe, const vector<unique_ptr<CJoueur>>& vuJoueurs) {
	// Hello, petit message car tu passera par là, déjà gg pour tout ce que tu as fait durant le projet et durant l'année :) tu as fait beaucoup de progrès !
	// Si jamais pour cette fonction tu dois utiliser CConsole::COS_AfficherGagnants(vsNomsGagnants, sNomEquipe);

	//cout << "Félicitations " << vJoueurs[uiIndiceJoueurGagnantPartie]->JOU_GetNomJoueur() << " vous avez gagné !" << endl;
}

void CRegleDameDePique::REG_AfficherMainJoueur(unsigned int uiIdJoueur, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe) {
	//pJoueur->JOU_GetMain()->PAQ_Afficher();
	// N'oublie pas que dans CConsole tu as un affichage de main ;)
}

void CRegleDameDePique::REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& muPointsEquipe) {
	for (auto it = muPointsEquipe.begin(); it != muPointsEquipe.end(); ++it)
	{
		cout << it->first->getEQU_numeroEquipe() << " : " << it->second << endl;
	}
}

/********************************************************/
/*                    NON - UTILISEES                   */
/********************************************************/

void CRegleDameDePique::REG_CalculerPointsManche(unique_ptr<CPaquet>& upPli, unsigned int uiIndiceJoueurGagnantPli, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unique_ptr<CPaquet>& upDefausse, const vector<unique_ptr<CJoueur>>& vuJoueurs) {}

void CRegleDameDePique::REG_MettreEnPlacePioche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs) {};
void CRegleDameDePique::REG_AfficherAfficherPli(unique_ptr<CPaquet>& upPli, vector<unsigned int> vuIdJoueurPli) {};