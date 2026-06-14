#ifndef _CPAQUETBASE_H
#define _CPAQUETBASE_H

#include <string>
#include <vector>
#include <random>
#include <stdexcept>
#include <memory>

#include "CPaquet.h"
#include "CCarte.h"

using namespace std;

class CPaquetBase : public CPaquet {
private :
	vector<unique_ptr<CCarte>> vcPAQ_paquet;
	vector<string> vsPAQ_couleurs;

public:
	CPaquetBase() {};

	virtual vector<unique_ptr<CCarte>>& PAQ_GetCartes() { return vcPAQ_paquet; }
	virtual vector<string>& PAQ_GetCouleurs() { return vsPAQ_couleurs; }
	virtual void PAQ_Afficher() const;
	virtual void PAQ_Melanger();
	virtual unique_ptr<CCarte> PAQ_RetirerCarte(int iIndiceCarte);
	virtual void PAQ_AjouterCarte(unique_ptr<CCarte> pCarteAAjouter);
};

#endif 
