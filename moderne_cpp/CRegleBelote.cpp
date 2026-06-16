#include "CRegleBelote.h"
#include "CPaquet.h"
#include "CJoueur.h"
#include "CCarte.h"
#include "CEquipe.h"
#include "CConsole.h"

/********************************************************/
/*                  SETTERS ET GETTERS                  */
/********************************************************/

bool CRegleBelote::REG_SetNbJoueur(unsigned int uiNbJoueurs) {
	if (uiNbJoueurs == 4)
	{
		return true;
	}

	return false;
}

void CRegleBelote::REG_SetAtout(string sNouveauAtout) { sREG_Atout = sNouveauAtout; }

/********************************************************/
/*                  METHODES DE CREGLE                  */
/********************************************************/


void CRegleBelote::REG_DebutPartie(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points){
    if (paquet != nullptr) {
        paquet->PAQ_Melanger();
    }

    REG_ConstituerEquipes(joueurs, points);
};

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


bool CRegleBelote::REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& points) {
	for (auto it = points.begin(); it != points.end(); ++it)
	{
		int iScoreEquipe = it->second;

		if (iScoreEquipe >= 200) // À changer à 1000 plus tard
		{
			return true;
		}
	}

	return false;
}


unsigned int CRegleBelote::REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int& uiJEU_IdJoueurCourrant)
{
	cout << "Une fois pret a lancer la manche, veuillez presser ENTREE pour continuer.\n";
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	CConsole::COS_NettoyerEcran();

	////////////////////////
	// DEBUT DE LA MANCHE //
	////////////////////////
	
	// Distribution (je n'ai pas fait 3 puis 2 vu qu'ici je mélange le paquet, je ne le coupe pas)
	sREG_Atout = "";
	REG_DistribuerCartes(joueurs, paquet);

	// Carte du milieu qu'on retourne
	unique_ptr<CCarte> pcCarteDuMilieu = paquet->PAQ_RetirerCarte();

	// Enchere du premier tour pour savoir quel joueur prend
	int iJoueurPreneur = REG_PremierTourEnchere(joueurs, uiJEU_IdJoueurCourrant, *pcCarteDuMilieu, points);

	if (iJoueurPreneur == -1) {
		// Enchere du deuxieme tour pour savoir quel joueur prend a quoi
		iJoueurPreneur = REG_DeuxiemeTourEnchere(joueurs, uiJEU_IdJoueurCourrant, pcCarteDuMilieu->CAR_GetCouleur(), points);
	}

	// Si personne n'a voulu prendre après les deux tours
	if (iJoueurPreneur == -1) {
		paquet->PAQ_AjouterCarte(move(pcCarteDuMilieu));
		REG_RemettreCartesDansPaquet(joueurs, paquet);
		uiJEU_IdJoueurCourrant = (uiJEU_IdJoueurCourrant + 1) % joueurs.size();

		CConsole::COS_NettoyerEcran();

		cout << "Les cartes ont été remises dans le paquet, on relance la manche.\n";
		return REG_DebutManche(paquet, joueurs, points, uiJEU_IdJoueurCourrant);
	}


	CConsole::COS_NettoyerEcran();

	cout << "**************************************************" << endl;
	cout << "               DEBUT DE LA MANCHE                 " << endl;
	cout << "**************************************************" << endl;

	cout << "\nLa manche peut commencer !" << endl;
	cout << joueurs[iJoueurPreneur]->JOU_GetNomJoueur() << " a pris. L'atout est : " << sREG_Atout << " <<<\n" << endl;

	// 4. Distribution du complément à 8 cartes
	for (size_t i = 0; i < joueurs.size(); ++i) {
		if (i == iJoueurPreneur) {
			joueurs[i]->JOU_GetMain()->PAQ_AjouterCarte(move(pcCarteDuMilieu));
		}
		
		int iNbCartesA_Donner = (i == iJoueurPreneur) ? 2 : 3;
		for (int c = 0; c < iNbCartesA_Donner; ++c) {
			joueurs[i]->JOU_GetMain()->PAQ_AjouterCarte(paquet->PAQ_RetirerCarte());
		}
	}
	cout << "Distribution terminee. Tous les joueurs ont 8 cartes." << endl;

	cout << "\nAppuyez sur ENTREE des que vous etes pret a demarrer.";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	CConsole::COS_NettoyerEcran();

	return uiJEU_IdJoueurCourrant;
}



bool CRegleBelote::REG_ConditionFinManche(const vector<unique_ptr<CJoueur>>& joueurs) {
	for (unsigned int uiBoucleJoueur = 0; uiBoucleJoueur < joueurs.size(); uiBoucleJoueur++){
		if (!joueurs[uiBoucleJoueur]->JOU_GetMain()->PAQ_GetCartes().empty()) {
			return false;
		}
	}
	return true;
};





void CRegleBelote::REG_JoueurSuivant(unsigned int uiIndiceJoueur) {}; // n’est jamais appelé directement, change indice joueur courant
void CRegleBelote::REG_MettreEnPlacePioche() {};

void CRegleBelote::REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet) {
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
};
bool CRegleBelote::REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& pPaquetJoueur) { return true; };

unsigned int CRegleBelote::REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli) { return 1; }; // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
void CRegleBelote::REG_CalculerPointsPli() {};
void CRegleBelote::REG_CalculerPointsManche() {}; // si nécessaire

void CRegleBelote::REG_RemettreCartesDansPaquet(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet) {
	for (unique_ptr<CJoueur>& joueur : joueurs) {
		vector<unique_ptr<CCarte>>& mainJoueur = joueur->JOU_GetMain()->PAQ_GetCartes();

		while (!mainJoueur.empty()) {
			paquet->PAQ_AjouterCarte(move(mainJoueur.back()));
			mainJoueur.pop_back();
		}
	}
}

/********************************************************/
/*                 METHODES SPECIALISEES                */
/********************************************************/

int CRegleBelote::REG_PremierTourEnchere(vector<unique_ptr<CJoueur>>& joueurs, unsigned int uiJoueurCourant, const CCarte& carteDuMilieu, map<unique_ptr<CEquipe>, int>& points)
{
	cout << "\n**************************************************" << endl;
	cout << "               DEBUT DES ENCHERES                 " << endl;
	cout << "**************************************************" << endl;

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

			// On appelle la fonction de la console pour afficher la main.
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

			CConsole::COS_AfficherEcranSecretJoueur(joueurs[uiJoueurQuiParle],uiNumEquipe,iScoreEquipe);

			cout << "\n\n[AU MILIEU] Carte retournee : " << carteDuMilieu << endl;
			cout << "[AU MILIEU] Atout propose   : " << carteDuMilieu.CAR_GetCouleur() << endl;

			char cChoix;
			cout << joueurs[uiJoueurQuiParle]->JOU_GetNomJoueur()
				<< ", voulez-vous prendre a " << carteDuMilieu.CAR_GetCouleur() << " ? (o/n) : ";
			cin >> cChoix;

			bPrend = (cChoix == 'o' || cChoix == 'O');
		}

		if (bPrend)
		{
			REG_SetAtout(carteDuMilieu.CAR_GetCouleur());
			return uiJoueurQuiParle;
		}

		uiJoueurQuiParle = (uiJoueurQuiParle + 1) % joueurs.size();
	}

	return -1;
}

int CRegleBelote::REG_DeuxiemeTourEnchere(vector<unique_ptr<CJoueur>>& joueurs, unsigned int uiJoueurCourant, const string& sCouleurRetourne, map<unique_ptr<CEquipe>, int>& points) {
	cout << "\n**************************************************" << endl;
	cout << "               DEUXIEME TOUR DES ENCHERES         " << endl;
	cout << "**************************************************" << endl;
	
	unsigned int uiJoueurQuiParle = uiJoueurCourant;
	string sAtoutPris;

	for (size_t i = 0; i < joueurs.size(); ++i) {
		bool bPrend = false;

		if (joueurs[uiJoueurQuiParle]->JOU_EstIa()) {
			bPrend = (rand() % 4 == 0); // 1 chance sur 4 de ne pas prendre, pour réduire la chance que l'IA prenne et désavantage le joueur humain

			if (bPrend) {
				// Ici on choisit au hasard, l'IA ne réfléchit pas en fonction de sa
				// main et on répète tant que la couleur est égale à celle proposée au premier tour
				
				vector<string> vsCouleurs = { "Coeur", "Carreau", "Trefle", "Pique" };
				do {
					sAtoutPris = vsCouleurs[rand() % 4];
				} while (sAtoutPris == sCouleurRetourne);

				cout << joueurs[uiJoueurQuiParle]->JOU_GetNomJoueur() << " : Je prends à " << sAtoutPris << " !" << endl;
			}
			else {
				cout << joueurs[uiJoueurQuiParle]->JOU_GetNomJoueur() << " : Je passe." << endl;
			}
		}
		else {
			unsigned int uiNumEquipe = 0;
			int iScoreEquipe = 0;

			for (auto it = points.begin(); it != points.end(); ++it) {
				vector<unsigned int> vNumeros = it->first->getEQU_equipe();
				for (unsigned int num : vNumeros) {
					if (num == uiJoueurQuiParle) {
						uiNumEquipe = it->first->getEQU_numeroEquipe();
						iScoreEquipe = it->second;
						break;
					}
				}
			}

			CConsole::COS_AfficherEcranSecretJoueur(joueurs[uiJoueurQuiParle], uiNumEquipe, iScoreEquipe);

			char cChoix;
			cout << "\n" << joueurs[uiJoueurQuiParle]->JOU_GetNomJoueur() << ", voulez-vous choisir une autre couleur d'atout ? (o/n) : ";
			cin >> cChoix;

			if (cChoix == 'o' || cChoix == 'O') {
				bPrend = true;
				cout << "Veuillez ecrire la couleur souhaitee (Coeur, Carreau, Trefle, Pique) : ";
				cin >> sAtoutPris;

				while (sAtoutPris == sCouleurRetourne) {
					cout << "ERREUR : Vous ne pouvez pas choisir la couleur d'origine. Autre choix : ";
					cin >> sAtoutPris;
				}
			}
		}

		if (bPrend)
		{
			REG_SetAtout(sAtoutPris);
			return uiJoueurQuiParle;
		}

		uiJoueurQuiParle = (uiJoueurQuiParle + 1) % joueurs.size();
	}
	return -1;
}



/********************************************************/
/*                       AFFICHAGE                      */
/********************************************************/

void CRegleBelote::REG_AfficherGagnantPartie(map<unique_ptr<CEquipe>, int>& points, const vector<unique_ptr<CJoueur>>& joueurs) {
	for (auto it = points.begin(); it != points.end(); ++it)
	{
		int iScoreEquipe = it->second;

		if (iScoreEquipe >= 200)
		{
			vector<unsigned int> vuIdsMembres = it->first->getEQU_equipe();

			vector<string> vsNomsGagnants;
			for (unsigned int id : vuIdsMembres) {
				if (id < joueurs.size()) {
					vsNomsGagnants.push_back(joueurs[id]->JOU_GetNomJoueur());
				}
			}

			string sNomEquipe = "Equipe " + to_string(it->first->getEQU_numeroEquipe());

			CConsole::COS_AfficherGagnants(vsNomsGagnants, sNomEquipe);

			break;
		}
	}
};



void CRegleBelote::REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vJoueurs, unsigned int uiIndiceJoueurGagnantPartie) {};
void CRegleBelote::REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur) {}; // appelle afficherpli
void CRegleBelote::REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& mJEU_points) {};
void CRegleBelote::REG_AfficherAfficherPli(unique_ptr<CPaquet> pPli, vector<unsigned int> vuIdJoueurPli) {};
