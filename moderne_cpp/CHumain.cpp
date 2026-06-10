#include "CHumain.h"
#include "CCarte.h"
#include <vector>
#include <iostream>
using namespace std;

CHumain::CHumain(): CJoueur()
{
}

CHumain::CHumain(string sJOU_nomJoueur): CJoueur(sJOU_nomJoueur)
{
}

unique_ptr<CCarte> CHumain::JOU_choixCarteAJouer()
{
	vector<unique_ptr<CCarte>>& upJOU_mainHumain = upJOU_main->getPAQ_cartes();
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
CHumain::~CHumain()
{
}
