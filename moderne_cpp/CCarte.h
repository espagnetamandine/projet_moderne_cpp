#ifndef _CCARTE_H
#define _CCARTE_H

#include <string>
#include <iostream>

using namespace std;

class CCarte {
private :

	// Attributs

	string sCAR_couleur;
	string sCAR_nom;
	unsigned int uiCAR_valeur;

public :

	// Constructeurs et destructeurs

	CCarte(string sCouleur, unsigned int uiValeur, string sNom = "empty")
	{
		sCAR_couleur = sCouleur;
		uiCAR_valeur = uiValeur;
		if (sNom == "empty")
		{
			CAR_MettreNom();
		}
		else
		{
			sCAR_nom = sNom;
		}
	};

	// Méthodes

	string CAR_GetCouleur() const { return sCAR_couleur; };
	string CAR_GetNom() const { return sCAR_nom; }
	unsigned int CAR_GetValeur() const { return uiCAR_valeur; };
	
	void CAR_MettreNom()
	{
		if (sCAR_couleur == "Joker")
		{
			sCAR_nom = "Joker";
			return;
		}

		switch (uiCAR_valeur)
		{
		case 1: 
			sCAR_nom = "As";
			break;
		case 11:
			sCAR_nom = "Valet";
			break;
		case 12:
			sCAR_nom = "Dame";
			break;
		case 13:
			sCAR_nom = "Roi";
			break;
		default:
			sCAR_nom = to_string(uiCAR_valeur);
			break;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const CCarte& CarteAAfficher)
	{
		if (CarteAAfficher.sCAR_couleur == "Joker")
		{
			os << CarteAAfficher.sCAR_couleur;
		}
		else {
			os << CarteAAfficher.sCAR_nom << " de " << CarteAAfficher.sCAR_couleur;
		}

		return os;
	}
};

#endif 