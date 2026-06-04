#include "CJoueur.h"
#include "CPaquet.h"
using namespace std;


CJoueur::CJoueur(): sNomJoueur(""),
                    iEquipe(0)
{
}
CJoueur::CJoueur(string sNomJoueur, int iEquipe) : sNomJoueur(sNomJoueur), 
                                                   iEquipe(iEquipe)
{
}
CPaquet CJoueur::getpMain()
{
	return pMain;
}
string CJoueur::getsNomJoueur()
{
	return sNomJoueur;
}
int CJoueur::getiEquipe()
{
	return iEquipe;
}
void CJoueur::setsNomJoueur(string sNouveauNom)
{
	sNomJoueur = sNouveauNom;
}
void CJoueur::setiEquipe(int iNouvelleEquipe)
{
	iEquipe = iNouvelleEquipe;
}
void CJoueur::setpMain(CPaquet pNouvelleMain)
{
	pMain = pNouvelleMain;
}
CJoueur::~CJoueur()
{

}