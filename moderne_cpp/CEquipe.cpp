#include "CEquipe.h"

using namespace std;

/********************************************************/
/*             CONSTRUCTEURS ET DESTRUCTEURS            */
/********************************************************/

CEquipe::CEquipe(): uiEQU_numeroEquipe(0)
{
}
CEquipe::CEquipe(vector<unsigned int> vuiEQU_equipe, unsigned int uiEQU_numeroEquipe) : vuiEQU_equipe(vuiEQU_equipe),
uiEQU_numeroEquipe(uiEQU_numeroEquipe)
{
}
CEquipe:: ~CEquipe()
{
}

/********************************************************/
/*                       METHODES                       */
/********************************************************/

vector<unsigned int> CEquipe::getEQU_equipe()
{
    return vuiEQU_equipe;
}
unsigned int CEquipe::getEQU_numeroEquipe()
{
    return uiEQU_numeroEquipe;
}
void CEquipe :: setEQU_numeroEquipe(unsigned int uiEQU_nouveauNumero)
{
    uiEQU_numeroEquipe = uiEQU_nouveauNumero;
}

void CEquipe::EQU_ajouterJoueur(unsigned int uiEQU_nouveauJoueur)
{
    for (unsigned int  uiEQU_numeroJoueur : vuiEQU_equipe)
    {
        if (uiEQU_numeroJoueur == uiEQU_nouveauJoueur)
        {
            throw std::invalid_argument("Le Joueur est déjà dans l'équipe");
        }

    }
    vuiEQU_equipe.push_back(uiEQU_nouveauJoueur);
}

void CEquipe::EQU_supprimerJoueur(unsigned int uiEQU_joueurASupprimer)
{
    vector<unsigned int >::iterator itJoueurASupprimer = find(vuiEQU_equipe.begin(), vuiEQU_equipe.end(), uiEQU_joueurASupprimer);
    if (itJoueurASupprimer == vuiEQU_equipe.end()) {
        throw std::invalid_argument("Le Joueur n'est déjà pas dans l'équipe");
    }
    vuiEQU_equipe.erase(itJoueurASupprimer);

}
