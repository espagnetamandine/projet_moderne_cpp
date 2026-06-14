#include "CHumain.h"

using namespace std;

// METHODES

unique_ptr<CCarte> CHumain::JOU_ChoixCarteAJouer()
{
	vector<unique_ptr<CCarte>>& upJOU_mainHumain = upJOU_main->PAQ_GetCartes();
	for (unsigned int uiBoucle = 0; uiBoucle < upJOU_mainHumain.size(); uiBoucle++)
	{
		cout << "carte " << uiBoucle << " : " << upJOU_mainHumain[uiBoucle] << endl;
	}
	cout << " CHoissisez une carte " << endl;
	unsigned int uiNumeroCarteChoisie = 0;
	cin >> uiNumeroCarteChoisie;
	while (uiNumeroCarteChoisie> upJOU_mainHumain.size() - 1)
	{
		cout << " Numéro de carte invalide, recommencez " << endl;
		cin >> uiNumeroCarteChoisie;
	}
	return move(upJOU_mainHumain[uiNumeroCarteChoisie]);
}
