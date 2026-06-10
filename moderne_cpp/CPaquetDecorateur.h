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

	virtual vector<unique_ptr<CCarte>>& getPAQ_Cartes() { return upPAQ_paquet->getPAQ_Cartes(); }
	virtual vector<string>& getPAQ_Couleurs() { return upPAQ_paquet->getPAQ_Couleurs(); }
	virtual void PAQ_Afficher() const { upPAQ_paquet->PAQ_Afficher(); }
	virtual void PAQ_Melanger() { upPAQ_paquet->PAQ_Melanger(); }
	virtual unique_ptr<CCarte> PAQ_RetirerCarte(int iIndiceCarte) { return upPAQ_paquet->PAQ_RetirerCarte(iIndiceCarte); }
	virtual void PAQ_AjouterCarte(unique_ptr<CCarte> pCarteAAjouter) { upPAQ_paquet->PAQ_AjouterCarte(move(pCarteAAjouter)); }
};

#endif 