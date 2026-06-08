#include "CJoueur.h"
#include "CPaquet.h"
using namespace std;


CJoueur::CJoueur(): sNomJoueur("")
{
}
CJoueur::CJoueur(string sNomJoueur) : sNomJoueur(sNomJoueur)                                        
{
}
CPaquetBase CJoueur::JOUEUR_GetpMain()
{
	return pMain;
}
string CJoueur::JOUEUR_GetsNomJoueur()
{
	return sNomJoueur;
}
void CJoueur::JOUEUR_SetsNomJoueur(string sNouveauNom)
{
	sNomJoueur = sNouveauNom;
}
void CJoueur::JOUEUR_SetpMain(CPaquetBase pNouvelleMain)
{
	pMain = pNouvelleMain;
}
CJoueur::~CJoueur()
{

}