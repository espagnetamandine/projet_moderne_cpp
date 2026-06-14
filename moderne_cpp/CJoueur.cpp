#include "CJoueur.h"
#include "CPaquet.h"
using namespace std;


CJoueur::CJoueur(string sJOU_nomJoueur = "Joueur") :sJOU_nomJoueur(sJOU_nomJoueur)
{
	upJOU_main = CPaquetManager::PAQ_CreerPaquet("Joueur"); // ou "Main du joueur"
}
unique_ptr<CPaquet>& CJoueur::JOU_GetMain()
{
	return upJOU_main;
}
string CJoueur::JOU_GetNomJoueur()
{
	return sJOU_nomJoueur;
}
void CJoueur::JOU_SetNomJoueur(string sJOU_nouveauNom)
{
	sJOU_nomJoueur = sJOU_nouveauNom;
}
void CJoueur::JOU_SetMain(unique_ptr<CPaquet> upJOU_nouvelleMain)
{
	upJOU_main = move(upJOU_nouvelleMain);
}
CJoueur::~CJoueur()
{

}