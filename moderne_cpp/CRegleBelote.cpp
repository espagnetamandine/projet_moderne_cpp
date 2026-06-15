#include "CRegleBelote.h"
#include "CPaquet.h"
#include "CJoueur.h"
#include "CCarte.h"
#include "CEquipe.h"
#include "CConsole.h"

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


bool CRegleBelote::REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& points) {
    for (auto it = points.begin(); it != points.end(); ++it)
    {
        int iScoreEquipe = it->second;

        if (iScoreEquipe >= 200) // à changer à 1000
        {
            cout << "\n[BELOTE] Fin de la partie ! L'equipe "
                << it->first->getEQU_numeroEquipe()
                << " a depasse les 200 points (" << iScoreEquipe << " pts) !" << endl;
            return true;
        }
    }

    return false;
};


unsigned int CRegleBelote::REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int& uiJEU_IdJoueurCourrant)
{
	cout << "\n-------------------------------------------------" << endl;
	cout << "               Debut de la manche                 " << endl;
	cout << "--------------------------------------------------" << endl;

	// Distribution (je n'ai pas fait 3 puis 2 vu qu'ici je mélange le paquet, je ne le coupe pas)
	sREG_Atout = "";
	REG_DistribuerCinqCartes(paquet, joueurs);

	// Carte du milieu
	unique_ptr<CCarte> pcCarteDuMilieu = paquet->PAQ_RetirerCarte();
	string sCouleurRetourne = pcCarteDuMilieu->CAR_GetCouleur();

	cout << "\nLa carte retournee au milieu est : " << *pcCarteDuMilieu << endl;
	cout << "L'atout propose est donc : " << sCouleurRetourne << "\n" << endl;

	// Enchere du premier tour pour savoir quel joueur prend
	int iJoueurPreneur = REG_PremierTourEnchere(joueurs, uiJEU_IdJoueurCourrant, *pcCarteDuMilieu, points);

	if (iJoueurPreneur == -1) {
		iJoueurPreneur = REG_DeuxiemeTourEnchere(joueurs, uiJEU_IdJoueurCourrant, sCouleurRetourne);
	}

	// Si personne n'a voulu prendre après les deux tours
	if (iJoueurPreneur == -1) {
		cout << "\n[BELOTE] Personne n'a pris ! Fin prematuree de la manche." << endl;
		return (uiJEU_IdJoueurCourrant + 1) % joueurs.size();
	}

	cout << "\n>>> Le contrat est valide ! " << joueurs[iJoueurPreneur]->JOU_GetNomJoueur()
		<< " a pris. L'atout est : " << sREG_Atout << " <<<\n" << endl;

	// 4. Distribution du complément à 8 cartes
	for (size_t i = 0; i < joueurs.size(); ++i) {
		if (i == iJoueurPreneur) {
			joueurs[i]->JOU_GetMain()->PAQ_AjouterCarte(move(pcCarteDuMilieu));
		}
		// Le preneur reçoit 2 cartes (en plus de la retourne), les autres en reçoivent 3
		int iNbCartesA_Donner = (i == iJoueurPreneur) ? 2 : 3;
		for (int c = 0; c < iNbCartesA_Donner; ++c) {
			joueurs[i]->JOU_GetMain()->PAQ_AjouterCarte(paquet->PAQ_RetirerCarte());
		}
	}
	cout << "[BELOTE] Distribution terminee. Tous les joueurs ont leurs 8 cartes." << endl;

	return uiJEU_IdJoueurCourrant;
}

// ============================================================================
// SOUS-FONCTIONS D'AIDE
// ============================================================================

void CRegleBelote::REG_DistribuerCinqCartes(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs) {
	unsigned int uiBoucleCarte;

	for (auto& joueur : joueurs) {
		joueur->JOU_GetMain()->PAQ_GetCartes().clear();
	}

	paquet->PAQ_Melanger();

	for (uiBoucleCarte = 0; uiBoucleCarte < 5; uiBoucleCarte++)
	{
		for (auto& joueur : joueurs) {
			joueur->JOU_GetMain()->PAQ_AjouterCarte(paquet->PAQ_RetirerCarte());
		}
	}

	cout << "[BELOTE] Distribution de 5 cartes par joueur" << endl;
}

int CRegleBelote::REG_PremierTourEnchere(vector<unique_ptr<CJoueur>>& joueurs, unsigned int uiJoueurCourant, const CCarte& carteDuMilieu, map<unique_ptr<CEquipe>, int>& points)
{
	unsigned int uiJoueurQuiParle = uiJoueurCourant;

	for (size_t i = 0; i < joueurs.size(); ++i)
	{
		bool bPrend = false;

		if (joueurs[uiJoueurQuiParle]->JOU_EstIa())
		{
			bPrend = (rand() % 2 == 0);
			cout << joueurs[uiJoueurQuiParle]->JOU_GetNomJoueur() << " (IA) : "
				<< (bPrend ? "Je prends !" : "Je passe.") << endl;
		}
		else
		{
			unsigned int uiNumEquipe = 0;
			int iScoreEquipe = 0;

			// On extrait l'équipe et le score pour faire plaisir à CConsole
			for (auto it = points.begin(); it != points.end(); ++it)
			{
				vector<unsigned int> vNumeros = it->first->getEQU_equipe();
				for (unsigned int num : vNumeros)
				{
					if (num == uiJoueurQuiParle)
					{
						uiNumEquipe = it->first->getEQU_numeroEquipe();
						iScoreEquipe = it->second;
						break;
					}
				}
			}

			// 1. Affichage secret
			CConsole::COS_AfficherEcranSecretJoueur(
				joueurs[uiJoueurQuiParle]->JOU_GetNomJoueur(),
				joueurs[uiJoueurQuiParle]->JOU_GetMain(),
				uiNumEquipe,
				iScoreEquipe
			);

			// 2. Tapis (Correction : carteDuMilieu.CAR_GetCouleur() avec un point '.')
			cout << "----------------------------------------------------------" << endl;
			cout << "[AU MILIEU] Carte retournee : " << carteDuMilieu << endl;
			cout << "[AU MILIEU] Atout propose   : " << carteDuMilieu.CAR_GetCouleur() << endl;
			cout << "----------------------------------------------------------\n" << endl;

			char cChoix;
			cout << joueurs[uiJoueurQuiParle]->JOU_GetNomJoueur()
				<< ", voulez-vous PRENDRE a la couleur " << carteDuMilieu.CAR_GetCouleur() << " ? (O/N) : ";
			cin >> cChoix;

			bPrend = (cChoix == 'o' || cChoix == 'O');
		}

		if (bPrend)
		{
			sREG_Atout = carteDuMilieu.CAR_GetCouleur(); // Correction ici aussi (.)
			return uiJoueurQuiParle;
		}

		uiJoueurQuiParle = (uiJoueurQuiParle + 1) % joueurs.size();
	}

	return -1;
}

int CRegleBelote::REG_DeuxiemeTourEnchere(vector<unique_ptr<CJoueur>>& joueurs, unsigned int uiJoueurCourant, const string& sCouleurRetourne) {
	cout << "\nPersonne n'a pris au premier tour. --- DEUXIEME TOUR ---" << endl;
	unsigned int uiJoueurQuiParle = uiJoueurCourant;

	for (size_t i = 0; i < joueurs.size(); ++i) {
		bool bPrend = false;

		if (joueurs[uiJoueurQuiParle]->JOU_EstIa()) {
			cout << joueurs[uiJoueurQuiParle]->JOU_GetNomJoueur() << " (IA) : Je passe." << endl;
			bPrend = false;
		}
		else {
			char cChoix;
			cout << "\n" << joueurs[uiJoueurQuiParle]->JOU_GetNomJoueur() << ", voulez-vous choisir une AUTRE couleur d'atout ? (O/N) : ";
			cin >> cChoix;

			if (cChoix == 'o' || cChoix == 'O') {
				bPrend = true;
				cout << "Veuillez ecrire la couleur souhaitee (Coeur, Carreau, Trefle, Pique) : ";
				cin >> sREG_Atout;

				while (sREG_Atout == sCouleurRetourne) {
					cout << "ERREUR : Vous ne pouvez pas choisir la couleur d'origine. Autre choix : ";
					cin >> sREG_Atout;
				}
			}
		}

		if (bPrend) return uiJoueurQuiParle;
		uiJoueurQuiParle = (uiJoueurQuiParle + 1) % joueurs.size();
	}
	return -1;
}



bool CRegleBelote::REG_ConditionFinManche() { return true; };

void CRegleBelote::REG_JoueurSuivant(unsigned int uiIndiceJoueur) {}; // n’est jamais appelé directement, change indice joueur courant
void CRegleBelote::REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points)
{
    if (joueurs.size() == 4)
    {

        vector<unsigned int> uiNumerosJoueursUne = { 0, 2 };
        vector<unsigned int> uiNumerosJoueursDeux = { 1, 3 };

        unique_ptr<CEquipe> peEquipeUne = make_unique<CEquipe>(uiNumerosJoueursUne, 1);
        unique_ptr<CEquipe> peEquipeDeux = make_unique<CEquipe>(uiNumerosJoueursDeux, 2);

        points.emplace(move(peEquipeUne), 0);
        points.emplace(move(peEquipeDeux), 0);

        cout << "Voici les equipes creees :" << endl;
        cout << " -> Equipe 1 : " << joueurs[0]->JOU_GetNomJoueur() << " & " << joueurs[2]->JOU_GetNomJoueur() << endl;
        cout << " -> Equipe 2 : " << joueurs[1]->JOU_GetNomJoueur() << " & " << joueurs[3]->JOU_GetNomJoueur() << endl;
    }
};
void CRegleBelote::REG_MettreEnPlacePioche() {};

void CRegleBelote::REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet) {};
bool CRegleBelote::REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& pPaquetJoueur) { return true; };

unsigned int CRegleBelote::REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli) { return 1; }; // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
void CRegleBelote::REG_CalculerPointsPli() {};
void CRegleBelote::REG_CalculerPointsManche() {}; // si nécessaire

void CRegleBelote::REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPli) {};
void CRegleBelote::REG_AfficherGagnantPartie(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPartie) {};
void CRegleBelote::REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur) {}; // appelle afficherpli
void CRegleBelote::REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& mJEU_points) {};


