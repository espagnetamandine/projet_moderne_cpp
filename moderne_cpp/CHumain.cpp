#include "CHumain.h"

using namespace std;

// METHODES

unsigned int CHumain::JOU_ChoixCarteAJouer()
{
	vector<unique_ptr<CCarte>>& upJOU_mainHumain = upJOU_main->PAQ_GetCartes();
	unsigned int uiChoixUtilisateur = 0;

	while (true)
	{
		cout << "Choisissez une carte a jouer (de 1 a " << upJOU_mainHumain.size() << ") : ";
		cin >> uiChoixUtilisateur;

		
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Erreur : Saisie invalide." << endl;
			continue;
		}

		if (uiChoixUtilisateur < 1 || uiChoixUtilisateur > upJOU_mainHumain.size())
		{
			cout << "Numero de carte invalide. Veuillez ressaisir (de 1 a " << upJOU_mainHumain.size() << ") : \n" << endl;
			continue;
		}

		break;
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return uiChoixUtilisateur - 1;
}