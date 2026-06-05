#include "Cia.h"
#include "CCarte.h"
#include "CPaquet.h"
#include <random>
#include <algorithm>
#include <vector>
using namespace std;


Cia::Cia(): CJoueur()
{
}

Cia::Cia(string sNomJoueur, int iEquipe) : CJoueur(sNomJoueur, iEquipe)
{
}

CCarte Cia::JOUEUR_Choix_Carte_A_Jouer()
{
	// Récupération de la main de l'IA
	vector <CCarte> pMainIA= pMain.getPaquet();
	
	// Creation d'un générateur random initialisé avec une graine aléatoire 
	default_random_engine generator(random_device{}());
	
	// Initialise la fonction random pour choisir un numéro aléatoire entre 0 et la taille - 1 de la main de l'IA
	uniform_int_distribution<int> distribution(0, pMainIA.size()-1);
	
	// Attribut un numéro aléatoire entre 0 et pMain.size()-1 à iNumeroAleatoire
	int iNumeroAleatoire = distribution(generator);
	
	// Retourne la carte avec l'indexe iNuméroAleatoire ( retourne une carte aléatoire)
	return pMainIA[iNumeroAleatoire];

}
Cia::~Cia()
{
}
