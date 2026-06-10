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
	CJoueur();
	CJoueur(string sJOU_NomJoueur);
	virtual unique_ptr<CCarte> JOU_choixCarteAJouer() = 0;
	unique_ptr<CPaquet>& getJOU_main();
	string getJOU_nomJoueur();
	void setJOU_main(unique_ptr<CPaquet> upJOU_nouvelleMain);
	void setJOU_nomJoueur(string sJOU_nouveauNom);
	virtual ~CJoueur();
};

#endif 