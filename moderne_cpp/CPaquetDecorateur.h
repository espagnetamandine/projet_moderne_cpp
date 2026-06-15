#ifndef _CPAQUETDecorateur_H
#define _CPAQUETDecorateur_H

#include <memory>
#include <vector>

#include "CPaquet.h"

using namespace std;

class CPaquetDecorateur : public CPaquet {
protected:

	// ATTRIBUTS

	unique_ptr<CPaquet> upPAQ_paquet;

public:

	// CONSTRUCTEURS ET DESTRUCTEURS

	CPaquetDecorateur(unique_ptr<CPaquet> pPaquet)
	{
		upPAQ_paquet = move(pPaquet);
	}

	// METHODES

	virtual vector<unique_ptr<CCarte>>& PAQ_GetCartes() { return upPAQ_paquet->PAQ_GetCartes(); }
	virtual vector<string>& PAQ_GetCouleurs() { return upPAQ_paquet->PAQ_GetCouleurs(); }
	virtual void PAQ_Afficher() const { upPAQ_paquet->PAQ_Afficher(); }
	virtual void PAQ_AfficherSansCouleurs() const { upPAQ_paquet->PAQ_AfficherSansCouleurs(); }
	virtual void PAQ_Melanger() { upPAQ_paquet->PAQ_Melanger(); }
	virtual unique_ptr<CCarte> PAQ_RetirerCarte(int iIndiceCarte) { return upPAQ_paquet->PAQ_RetirerCarte(iIndiceCarte); }
	virtual void PAQ_AjouterCarte(unique_ptr<CCarte> pCarteAAjouter) { upPAQ_paquet->PAQ_AjouterCarte(move(pCarteAAjouter)); }
};

#endif 