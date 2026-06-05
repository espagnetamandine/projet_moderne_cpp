#ifndef _CPAQUET_H
#define _CPAQUET_H

#include "CCarte.h"

class CPaquet {

public:
	virtual ~CPaquet() = default;

	virtual vector<unique_ptr<CCarte>>& getPAQ_cartes() = 0;
	virtual vector<string>& getPAQ_couleurs() = 0;
	virtual void PAQ_melanger() = 0;
	virtual void PAQ_afficher() const = 0;
	virtual unique_ptr<CCarte> PAQ_retirerCarte(int iIndiceCarte = -1) = 0;
	virtual void PAQ_ajouterCarte(unique_ptr<CCarte> pCarteAAjouter) = 0;
};

#endif 