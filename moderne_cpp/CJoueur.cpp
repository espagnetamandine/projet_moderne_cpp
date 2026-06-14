#include "CJoueur.h"

using namespace std;

// CONSTRUCTEURS ET DESTRUCTEURS

CJoueur::CJoueur(string sJOU_nomJoueur) : sJOU_nomJoueur(sJOU_nomJoueur)
{
	upJOU_main = CPaquetManager::PAQ_CreerPaquet("Joueur"); // ou "Main du joueur"
}
CJoueur::~CJoueur()
{

}

// METHODES

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