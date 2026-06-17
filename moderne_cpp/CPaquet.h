#ifndef _CPAQUET_H
#define _CPAQUET_H

#include "CCarte.h"

#include <vector>
#include <memory>
#include <string>

using namespace std;

class CPaquet {

public:
	virtual ~CPaquet() = default;

	virtual vector<unique_ptr<CCarte>>& PAQ_GetCartes() = 0;
	virtual vector<string>& PAQ_GetCouleurs() = 0;
	virtual void PAQ_Melanger() = 0;
	virtual void PAQ_Afficher() const = 0;
	virtual void PAQ_AfficherSansCouleurs() const = 0;
	virtual void PAQ_AfficherAvecIdentifiant() const = 0;
	virtual unique_ptr<CCarte> PAQ_RetirerCarte(int iIndiceCarte = -1) = 0;
	virtual void PAQ_AjouterCarte(unique_ptr<CCarte> pCarteAAjouter) = 0;
};

#endif 
