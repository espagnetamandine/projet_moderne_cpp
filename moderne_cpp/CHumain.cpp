#include "CHumain.h"

using namespace std;

// METHODES

unique_ptr<CCarte> CHumain::JOU_ChoixCarteAJouer()
{
	vector<unique_ptr<CCarte>>& upJOU_mainHumain = upJOU_main->PAQ_GetCartes();
	
	cout << "Choisissez une carte a jouer (de 1 a " << upJOU_mainHumain.size() << ") : ";
	unsigned int uiChoixUtilisateur = 0;
	cin >> uiChoixUtilisateur;

	while (uiChoixUtilisateur < 1 || uiChoixUtilisateur > upJOU_mainHumain.size())
	{
		cout << "Numero de carte invalide. Veuillez ressaisir (de 1 a " << upJOU_mainHumain.size() << ") : ";
		cin >> uiChoixUtilisateur;
	}

	unsigned int uiIndexVecteur = uiChoixUtilisateur - 1;

	unique_ptr<CCarte> carteChoisie = move(upJOU_mainHumain[uiIndexVecteur]);

	upJOU_mainHumain.erase(upJOU_mainHumain.begin() + uiIndexVecteur);

	return carteChoisie;
}
