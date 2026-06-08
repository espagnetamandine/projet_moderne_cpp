#ifndef _CEQUIPE_H
#define _CEQUIPE_H

#include "CJoueur.h"

#include <vector>

using namespace std;

class CEquipe
{
private:
	vector<CJoueur*> vjEquipe;
	unsigned int uiNumeroEquipe;
public:
	CEquipe();
	CEquipe(vector<CJoueur*> vjEquipe, unsigned int uiNumeroEquipe);
	void EQU_AjouterJoueur(CJoueur* AjouterJoueur);
	void EQU_SupprimerJoueur(CJoueur* SupprimerJoueur);
	vector<CJoueur*> EQU_GetvjEquipe();
	unsigned int EQU_GetuiNumeroEquipe();
	void EQU_SetuiNumeroEquipe(unsigned int uiNouveauNumero);
	~CEquipe();
};

#endif