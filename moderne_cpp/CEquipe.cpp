#include "CEquipe.h"
#include "CJoueur.h"

#include <algorithm>

using namespace std;


CEquipe::CEquipe(): uiNumeroEquipe(0)
{
}

CEquipe::CEquipe(vector<CJoueur*> vjEquipe, unsigned int uiNumeroEquipe) : vjEquipe(vjEquipe),
uiNumeroEquipe(uiNumeroEquipe)
{
}
vector<CJoueur*> CEquipe::EQU_GetvjEquipe()
{
    return vjEquipe;
}
unsigned int CEquipe::EQU_GetuiNumeroEquipe()
{
    return uiNumeroEquipe;
}
void CEquipe::EQU_SetuiNumeroEquipe(unsigned int uiNouveauNumero)
{
    uiNumeroEquipe = uiNouveauNumero;
}

void CEquipe::EQU_AjouterJoueur(CJoueur* pAjouterJoueur)
{
    for (CJoueur* pJoueur : vjEquipe)
    {
        if (pJoueur->JOUEUR_GetsNomJoueur() == pAjouterJoueur->JOUEUR_GetsNomJoueur())
        {
            throw std::invalid_argument("Le Joueur est déjà dans l'équipe");
        }

    }
    vjEquipe.push_back(pAjouterJoueur);
}

void CEquipe::EQU_SupprimerJoueur(CJoueur* pSupprimerJoueur)
{
    vector<CJoueur*>::iterator itJoueurASupprimer = find(vjEquipe.begin(), vjEquipe.end(), pSupprimerJoueur);
    if (itJoueurASupprimer == vjEquipe.end()) {
        throw std::invalid_argument("Le Joueur n'est déjà pas dans l'équipe");
    }
    vjEquipe.erase(itJoueurASupprimer);

}

CEquipe:: ~CEquipe()
{
}