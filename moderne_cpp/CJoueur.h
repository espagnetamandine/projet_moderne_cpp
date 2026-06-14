#ifndef _CJOUEUR_H
#define _CJOUEUR_H
#include <string>
#include "CPaquetManager.h"
#include "CPaquetBase.h"
#include "CCarte.h"

using namespace std;

class CJoueur
{
protected:
	string sJOU_nomJoueur;
	unique_ptr<CPaquet> upJOU_main;
public:
	CJoueur(string sJOU_NomJoueur = "Joueur");
	virtual unique_ptr<CCarte> JOU_ChoixCarteAJouer() = 0;
	unique_ptr<CPaquet>& JOU_GetMain();
	string JOU_GetNomJoueur();
	void JOU_SetMain(unique_ptr<CPaquet> upJOU_nouvelleMain);
	void JOU_SetNomJoueur(string sJOU_nouveauNom);
	virtual ~CJoueur();
};

#endif 