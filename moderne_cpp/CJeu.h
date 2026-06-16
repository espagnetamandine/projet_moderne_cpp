#ifndef _CJEU_H
#define _CJEU_H

#include <vector>
#include <map>
#include <string>
#include <memory>

using namespace std;

class CRegle;
class CCarte;
class CPaquet;
class CJoueur;
class CEquipe;

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

public:
	CJeu(string sNom);
	~CJeu();

	string JEU_GetNom() { return sJEU_nom; }

	string JEU_GetNomJoueur(unsigned int uiIdJoueur);

	unsigned int JEU_GetIndiceJoueurCourant() { return uiJEU_IdJoueurCourrant; }
	void JEU_SetIndiceJoueurCourant(unsigned int uiIndiceJoueur) { uiJEU_IdJoueurCourrant = uiIndiceJoueur; };

	void JEU_SetStrategieRegle(unique_ptr<CRegle> regle);
	void JEU_AjouterJoueur(unique_ptr<CJoueur> ujJoueurAAjouter) { vjJEU_joueurs.push_back(move(ujJoueurAAjouter)); }
	void JEU_JouerPartie();




	void JEU_AfficherPoints();
	void JEU_AfficherEquipe();
	void JEU_AfficherPli();
	void JEU_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur);

	bool JEU_SetNombreJoueur(unsigned int uiNbJoueurs);
};
#endif