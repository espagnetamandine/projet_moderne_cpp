#ifndef _CEQUIPE_H
#define _CEQUIPE_H

#include "CJoueur.h"

#include <vector>

using namespace std;

class CEquipe
{
private:
	vector< unsigned int> vuiEQU_equipe;
	unsigned int uiEQU_numeroEquipe;
public:
	CEquipe();
	CEquipe(vector<unsigned int> vuiEQU_equipe, unsigned int uiEQU_numeroEquipe);
	void EQU_ajouterJoueur(unsigned int uiEQU_nouveauJoueur);
	void EQU_supprimerJoueur(unsigned int uiEQU_joueurASupprimer);
	vector<unsigned int> getEQU_equipe();
	unsigned int getEQU_numeroEquipe();
	void setEQU_numeroEquipe(unsigned int uiEQU_nouveauNumero);
	~CEquipe();
};

#endif