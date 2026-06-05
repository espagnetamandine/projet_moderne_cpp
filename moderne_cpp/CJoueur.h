#ifndef _CJOUEUR_H
#define _CJOUEUR_H
#include <string>
#include "CPaquet.h"
#include "CPaquetBase.h"
#include "CCarte.h"

using namespace std;

class CJoueur
{
protected:
	string sNomJoueur;
	CPaquetBase pMain;
public:
	CJoueur();
	CJoueur(string sNomJoueur);
	virtual CCarte JOUEUR_Choix_Carte_A_Jouer() = 0;
	CPaquetBase JOUEUR_GetpMain();
	string JOUEUR_GetsNomJoueur();
	void JOUEUR_SetpMain(CPaquetBase pNouvelleMain);
	void JOUEUR_SetsNomJoueur(string sNouveauNom);
	virtual ~CJoueur();
};

#endif 