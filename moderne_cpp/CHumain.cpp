#include "CHumain.h"
#include "CCarte.h"
#include <vector>
#include <iostream>
using namespace std;

CHumain::CHumain(): CJoueur()
{
}

CHumain::CHumain(string sNomJoueur, int iEquipe): CJoueur(sNomJoueur,iEquipe)
{
}

CCarte CHumain::JOUEUR_Choix_Carte_A_Jouer()
{
	vector<CCarte> pMainHumain = pMain.getPaquet();
	for (unsigned int uiBoucle = 0; uiBoucle < pMainHumain.size(); uiBoucle++)
	{
		cout << "carte " << uiBoucle << " : " << pMainHumain[uiBoucle] << endl;
	}
	cout << " CHoissisez une carte " << endl;
	unsigned int uiNumeroCarteChoisie = 0;
	cin >> uiNumeroCarteChoisie;
	while (uiNumeroCarteChoisie>pMainHumain.size() - 1)
	{
		cout << " Numéro de carte invalide, recommencez " << endl;
		cin >> uiNumeroCarteChoisie;
	}
	return pMainHumain[uiNumeroCarteChoisie];
}
CHumain::~CHumain()
{
}
