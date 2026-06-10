#include "CJoueur.h"
#include "CPaquet.h"
using namespace std;


CJoueur::CJoueur(): sJOU_nomJoueur("")
{
}
CJoueur::CJoueur(string sJOU_nomJoueur) :sJOU_nomJoueur(sJOU_nomJoueur)
{
}
unique_ptr<CPaquet>& CJoueur::getJOU_main()
{
	return upJOU_main;
}
string CJoueur::getJOU_nomJoueur()
{
	return sJOU_nomJoueur;
}
void CJoueur::setJOU_nomJoueur(string sJOU_nouveauNom)
{
	sJOU_nomJoueur = sJOU_nouveauNom;
}
void CJoueur::setJOU_main(unique_ptr<CPaquet> upJOU_nouvelleMain)
{
	upJOU_main = move(upJOU_nouvelleMain);
}
CJoueur::~CJoueur()
{

}