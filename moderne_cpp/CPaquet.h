
#ifndef _CPAQUET_H
#define _CPAQUET_H

#include "CCarte.h"

class CPaquet {

public:
	virtual ~CPaquet() = default;

	virtual vector<CCarte>& getPAQ_cartes() = 0;
	virtual vector<string>& getPAQ_couleurs() = 0;
	virtual void PAQ_melanger() = 0;
	virtual void PAQ_afficher() const = 0;
};

#endif 
