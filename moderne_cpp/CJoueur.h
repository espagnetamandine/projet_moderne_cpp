#ifndef _CJOUEUR_H
#define _CJOUEUR_H
#include <string>
#include "CPaquet.h"
#include "CCarte.h"
class CJoueur
{
protected:
	std::string sNomJoueur;
	CPaquet pMain;
	int iEquipe;
public:
	CJoueur();
	CJoueur(std::string sNomJoueur, int iEquipe);
	virtual CCarte JOUEUR_Choix_Carte_A_Jouer() = 0;
	CPaquet getpMain();
	std::string getsNomJoueur();
	int getiEquipe();
	void setiEquipe(int iNouvelleEquipe);
	void setpMain(CPaquet pNouvelleMain);
	void setsNomJoueur(std::string sNouveauNom);
	virtual ~CJoueur();
};

#endif 