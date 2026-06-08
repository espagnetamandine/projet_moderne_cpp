#ifndef _CPAQUETDecorateur_H
#define _CPAQUETDecorateur_H

#include <memory>
#include <vector>

#include "CPaquet.h"
#include "CCarte.h"

using namespace std;

class CPaquetDecorateur : public CPaquet {
protected:
	unique_ptr<CPaquet> upPAQ_paquet;

public:
	CPaquetDecorateur(unique_ptr<CPaquet> pPaquet)
	{
		upPAQ_paquet = move(pPaquet);
	}

	virtual vector<unique_ptr<CCarte>>& getPAQ_cartes() { return upPAQ_paquet->getPAQ_cartes(); }
	virtual vector<string>& getPAQ_couleurs() { return upPAQ_paquet->getPAQ_couleurs(); }
	virtual void PAQ_afficher() const { upPAQ_paquet->PAQ_afficher(); }
	virtual void PAQ_melanger() { upPAQ_paquet->PAQ_melanger(); }
	virtual unique_ptr<CCarte> PAQ_retirerCarte(int iIndiceCarte) { return upPAQ_paquet->PAQ_retirerCarte(iIndiceCarte); }
	virtual void PAQ_ajouterCarte(unique_ptr<CCarte> pCarteAAjouter) { upPAQ_paquet->PAQ_ajouterCarte(move(pCarteAAjouter)); }
};

#endif 