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
	string sPAQ_nomPaquet;
	vector<unique_ptr<CCarte>> vcPAQ_paquet;
	vector<string> vsPAQ_couleurs;

public:
	CPaquetBase() { sPAQ_nomPaquet = "Paquet Vide"; };

	virtual vector<unique_ptr<CCarte>>& getPAQ_cartes() { return vcPAQ_paquet; }
	virtual vector<string>& getPAQ_couleurs() { return vsPAQ_couleurs; }
	virtual void PAQ_afficher() const;
	virtual void PAQ_melanger();
	virtual unique_ptr<CCarte> PAQ_retirerCarte(int iIndiceCarte);
	virtual void PAQ_ajouterCarte(unique_ptr<CCarte> pCarteAAjouter);
};

#endif 