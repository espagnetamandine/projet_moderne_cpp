#ifndef _CPAQUETBASE_H
#define _CPAQUETBASE_H

#include <string>
#include <vector>
#include <random>

#include "CPaquet.h"
#include "CCarte.h"

using namespace std;

class CPaquetBase : public CPaquet {
private :
	string sPAQ_nomPaquet;
	vector<CCarte> vcPAQ_paquet;
	vector<string> vsPAQ_couleurs;

public:
	CPaquetBase() { sPAQ_nomPaquet = "Paquet Vide"; };

	virtual vector<CCarte>& getPAQ_cartes() { return vcPAQ_paquet; }
	virtual vector<string>& getPAQ_couleurs() { return vsPAQ_couleurs; }
	virtual void PAQ_afficher() const;
	virtual void PAQ_melanger();
};

#endif 