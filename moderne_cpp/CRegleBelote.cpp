#include "CRegleBelote.h"

bool CRegleBelote::REG_SetNbJoueur(unsigned int uiNbJoueurs)
{
	if (uiNbJoueurs == 4)
	{
		return true;
	}

	return false;
}

void CRegleBelote::REG_DebutPartie(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points){
    if (paquet != nullptr) {
        paquet->PAQ_Melanger();
    }

    REG_ConstituerEquipes(joueurs, points);
};


bool CRegleBelote::REG_ConditionFinPartie() { return true; };
void CRegleBelote::REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points) {}; // ajouter 1 à la manche
bool CRegleBelote::REG_ConditionFinManche() { return true; };

void CRegleBelote::REG_JoueurSuivant(unsigned int uiIndiceJoueur) {}; // n’est jamais appelé directement, change indice joueur courant
void CRegleBelote::REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points)
{
    if (joueurs.size() == 4)
    {
        unique_ptr<CEquipe> peEquipeUne = make_unique<CEquipe>("Equipe 1");
        peEquipeUne->EQU_ajouterJoueur(0);
        peEquipeUne->EQU_ajouterJoueur(2);

        unique_ptr<CEquipe> peEquipeDeux = make_unique<CEquipe>("Equipe 2");
        peEquipeDeux->EQU_ajouterJoueur(1);
        peEquipeDeux->EQU_ajouterJoueur(3);

        points[move(peEquipeUne)] = 0;
        points[move(peEquipeDeux)] = 0;

        cout << "Voici les équipes créées :" << endl;
        cout << " -> Equipe 1 : " << joueurs[0]->JOU_GetNomJoueur() << " & " << joueurs[2]->JOU_GetNomJoueur() << endl;
        cout << " -> Equipe 2 : " << joueurs[1]->JOU_GetNomJoueur() << " & " << joueurs[3]->JOU_GetNomJoueur() << endl;
    }
};
void CRegleBelote::REG_MettreEnPlacePioche() {};

void CRegleBelote::REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet) {};
bool CRegleBelote::REG_PremiereCarte(CCarte& carte) { return true; };
bool CRegleBelote::REG_CarteValide(CCarte& carte) { return true; };

unsigned int CRegleBelote::REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli) { return 1; }; // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
void CRegleBelote::REG_CalculerPointsPli() {};
void CRegleBelote::REG_CalculerPointsManche() {}; // si nécessaire

void CRegleBelote::REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPli) {};
void CRegleBelote::REG_AfficherGagnantPartie(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPartie) {};
void CRegleBelote::REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur) {}; // appelle afficherpli
void CRegleBelote::REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& mJEU_points) {};


