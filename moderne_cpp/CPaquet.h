
#ifndef _CPAQUET_H
#define _CPAQUET_H

#include "CCarte.h"

class CPaquet {

public:
	virtual ~CPaquet() = default;

	virtual vector<unique_ptr<CCarte>>& getPAQ_Cartes() = 0;
	virtual vector<string>& getPAQ_Couleurs() = 0;
	virtual void PAQ_Melanger() = 0;
	virtual void PAQ_Afficher() const = 0;
	virtual unique_ptr<CCarte> PAQ_RetirerCarte(int iIndiceCarte = -1) = 0;
	virtual void PAQ_AjouterCarte(unique_ptr<CCarte> pCarteAAjouter) = 0;
};

#endif 
