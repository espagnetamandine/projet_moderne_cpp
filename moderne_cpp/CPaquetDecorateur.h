#ifndef _CPAQUETDecorateur_H
#define _CPAQUETDecorateur_H

#include <memory>
#include <vector>

#include "CPaquet.h"
#include "CCarte.h"

using namespace std;

class CPaquetDecorateur : public CPaquet {
protected:
	unique_ptr<CPaquet> upPAD_paquet;

public:
	CPaquetDecorateur(unique_ptr<CPaquet> paquet)
	{
		upPAD_paquet = move(paquet);
	}

	virtual vector<unique_ptr<CCarte>>& getPAQ_cartes() { return upPAD_paquet->getPAQ_cartes(); }
	virtual vector<string>& getPAQ_couleurs() { return upPAD_paquet->getPAQ_couleurs(); }
	virtual void PAQ_afficher() const { upPAD_paquet->PAQ_afficher(); }
	virtual void PAQ_melanger() { upPAD_paquet->PAQ_melanger(); }
	virtual unique_ptr<CCarte> PAQ_retirerCarte(int iIndiceCarte) { return upPAD_paquet->PAQ_retirerCarte(iIndiceCarte); }
	virtual void PAQ_ajouterCarte(unique_ptr<CCarte> pCarteAAjouter) { upPAD_paquet->PAQ_ajouterCarte(move(pCarteAAjouter)); }
};

#endif 