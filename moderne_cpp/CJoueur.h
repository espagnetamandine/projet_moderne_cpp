#ifndef _CJOUEUR_H
#define _CJOUEUR_H

#include "CPaquet.h"
#include "CPaquetManager.h"

#include <string>

using namespace std;

class CJoueur
{
protected:

	// Attributs

	string sJOU_nomJoueur;
	unique_ptr<CPaquet> upJOU_main;

public:

	// Constructeurs et destructeurs

	CJoueur(string sJOU_nomJoueur = "Joueur");
	virtual ~CJoueur();

	// Méthodes

	virtual unsigned int JOU_ChoixCarteAJouer() = 0;
	unique_ptr<CPaquet>& JOU_GetMain();
	string JOU_GetNomJoueur();
	void JOU_SetMain(unique_ptr<CPaquet> upJOU_nouvelleMain);
	void JOU_SetNomJoueur(string sJOU_nouveauNom);

	virtual bool JOU_EstIa() const { return false; }
};

#endif 