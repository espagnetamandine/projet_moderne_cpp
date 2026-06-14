
#ifndef _CJEU_H
#define _CJEU_H

#include "CRegle.h"
#include "CCarte.h"
#include "CPaquet.h"
#include "CJoueur.h"
#include "CEquipe.h"

#include <vector>
#include <map>

using namespace std;

class CJeu {
private:
	string sJEU_nom;

	unique_ptr<CRegle> prJEU_strategieRegle;

	unique_ptr<CPaquet> pJEU_paquetDeCartes;
	unique_ptr<CPaquet> pJEU_defausse;
	unique_ptr<CPaquet> pJEU_pli;
	vector<unsigned int> vuJEU_idJoueurPli;

	vector<unique_ptr<CJoueur>> vjJEU_joueurs;
	map<unique_ptr<CEquipe>, int> mJEU_points;
	unsigned int uiJEU_IdJoueurCourrant;

	unsigned int uiJEU_compteurManche;
	unsigned int uiJEU_compteurPli;

public:
	CJeu(string sNom);

	string JEU_GetNom() { return sJEU_nom; }

	string JEU_GetNomJoueur(unsigned int uiIdJoueur) { return vjJEU_joueurs[uiIdJoueur].get()->JOU_GetNomJoueur(); }
	unsigned int JEU_GetIndiceJoueurCourant() { return uiJEU_IdJoueurCourrant; }
	void JEU_SetIndiceJoueurCourant(unsigned int uiIndiceJoueur) { uiJEU_IdJoueurCourrant = uiIndiceJoueur; };

	void JEU_IncrementerCompteurManche() { uiJEU_compteurManche++; }
	void JEU_IncrementerCompteurPli() { uiJEU_compteurPli++; }
	
	void JEU_SetStrategieRegle(unique_ptr<CRegle> regle) { prJEU_strategieRegle = move(regle); }
	void JEU_AjouterJoueur(unique_ptr<CJoueur> ujJoueurAAjouter) { vjJEU_joueurs.push_back(move(ujJoueurAAjouter)); }
	void JEU_JouerPartie(); 

	void JEU_AfficherPoints(); // appelle à afficher points de règles
	void JEU_AfficherEquipe(); // appelle à afficher équipe de règles
	void JEU_AfficherPli();
	void JEU_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur); // appelle à afficher main joueur de règle car ça affiche la main, le nom du joueur, le pli et les équipes l’interface peut changer en fonction des jeux

	// PLUS

	bool JEU_SetNombreJoueur(unsigned int uiNbJoueurs) {
		return prJEU_strategieRegle->REG_SetNbJoueur(uiNbJoueurs);
	}


};
#endif 