#include "Cia.h"
#include "CCarte.h"
#include "CPaquet.h"
#include <random>
#include <algorithm>
#include <vector>
#include "CJoueur.h"
using namespace std;

unique_ptr<CCarte> Cia::JOU_ChoixCarteAJouer()
{
	// Récupération de la main de l'IA
	vector<unique_ptr<CCarte>>& upJOU_mainIA= upJOU_main->PAQ_GetCartes();
	
	// Creation d'un générateur random initialisé avec une graine aléatoire 
	default_random_engine generator(random_device{}());
	
	// Initialise la fonction random pour choisir un numéro aléatoire entre 0 et la taille - 1 de la main de l'IA
	uniform_int_distribution<int> distribution(0, upJOU_mainIA.size()-1);
	
	// Attribut un numéro aléatoire entre 0 et pMain.size()-1 à iNumeroAleatoire
	int iNumeroAleatoire = distribution(generator);
	
	// Retourne la carte avec l'indexe iNuméroAleatoire ( retourne une carte aléatoire)
	return move(upJOU_mainIA[iNumeroAleatoire]);

}
Cia::~Cia()
{
}
