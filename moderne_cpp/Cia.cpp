#include "Cia.h"

using namespace std;

// METHODES

unsigned int Cia::JOU_ChoixCarteAJouer()
{
	vector<unique_ptr<CCarte>>& upJOU_mainIA = upJOU_main->PAQ_GetCartes();

	default_random_engine generator(random_device{}());
	uniform_int_distribution<int> distribution(0, upJOU_mainIA.size() - 1);

	unsigned int iNumeroAleatoire = distribution(generator);

	return iNumeroAleatoire;
}