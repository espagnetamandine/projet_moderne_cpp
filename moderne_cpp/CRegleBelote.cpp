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
/*                    METHODES DE JEU                   */
/********************************************************/

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
	cout << joueurs[iJoueurPreneur]->JOU_GetNomJoueur() << " a pris. L'atout est : " << sREG_Atout << endl;

	// Distribution du reste des cartes
	for (size_t sBoucleJoueur = 0; sBoucleJoueur < joueurs.size(); ++sBoucleJoueur) {
		if (sBoucleJoueur == iJoueurPreneur) {
			joueurs[sBoucleJoueur]->JOU_GetMain()->PAQ_AjouterCarte(move(pcCarteDuMilieu));
		}

		unsigned int iNbCartesADonner;
		if (sBoucleJoueur == iJoueurPreneur)
		{
			iNbCartesADonner = 2;
		}
		else {
			iNbCartesADonner = 3;
		}
		for (unsigned int uiBoucle = 0; uiBoucle < iNbCartesADonner; ++uiBoucle) {
			joueurs[sBoucleJoueur]->JOU_GetMain()->PAQ_AjouterCarte(paquet->PAQ_RetirerCarte());
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

/********************************************************/
/*                    MISES EN PLACE                    */
/********************************************************/

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

void CRegleBelote::REG_RemettreCartesDansPaquet(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet) {
	for (unique_ptr<CJoueur>& joueur : joueurs) {
		vector<unique_ptr<CCarte>>& mainJoueur = joueur->JOU_GetMain()->PAQ_GetCartes();

		while (!mainJoueur.empty()) {
			paquet->PAQ_AjouterCarte(move(mainJoueur.back()));
			mainJoueur.pop_back();
		}
	}
}





void CRegleBelote::REG_JoueurSuivant(unsigned int uiIndiceJoueur) {}; // n’est jamais appelé directement, change indice joueur courant
void CRegleBelote::REG_MettreEnPlacePioche() {};


bool CRegleBelote::REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& pPaquetJoueur, const unique_ptr<CPaquet>& pPli, const vector<unsigned int>& vuIdJoueurPli)
{
	vector<unique_ptr<CCarte>>& cartesDuPli = pPli->PAQ_GetCartes();
	vector<unique_ptr<CCarte>>& mainJoueur = pPaquetJoueur->PAQ_GetCartes();

	// Cas numéro 1 : Le pli est vide, tout est autorisé.
	if (cartesDuPli.empty()) {
		return true;
	}

	string sCouleurDemandee = cartesDuPli[0]->CAR_GetCouleur();
	string sCouleurJouee = carte.CAR_GetCouleur();
	unsigned int uiValeurJouee = carte.CAR_GetValeur();

	// Infos de la main du joueur //
	bool bPossedeCouleurDemandee = false;
	bool bPossedeAtout = false;
	unsigned int uiForceAtoutMain = 0;

	for (size_t i = 0; i < mainJoueur.size(); ++i) {
		if (mainJoueur[i]->CAR_GetCouleur() == sCouleurDemandee) {
			bPossedeCouleurDemandee = true;
		}
		if (mainJoueur[i]->CAR_GetCouleur() == sREG_Atout) {
			bPossedeAtout = true;
			unsigned int uiForce = REG_ObtenirForceAtout(mainJoueur[i]->CAR_GetValeur());
			if (uiForce > uiForceAtoutMain) {
				uiForceAtoutMain = uiForce;
			}
		}
	}

	// Infos de la meilleure carte du pli //
	unsigned int uiIdxMeilleureCarte = REG_ObtenirMeilleurCarteTapis(cartesDuPli, sCouleurDemandee, sREG_Atout);
	unsigned int uiIdMaitreActuel = vuIdJoueurPli[uiIdxMeilleureCarte];

	unsigned int uiIdJoueurCourant = (vuIdJoueurPli.back() + 1) % 4;
	bool bPartenaireEstMaitre = (uiIdMaitreActuel % 2 == uiIdJoueurCourant % 2);

	unsigned int uiValeurMaitreTapis = cartesDuPli[uiIdxMeilleureCarte]->CAR_GetValeur();
	bool bTapisCoupe = (cartesDuPli[uiIdxMeilleureCarte]->CAR_GetCouleur() == sREG_Atout);

	//////////////////////
	// Règles générales //
	//////////////////////

	// Cas numéro 2.0 : L'atout n'est pas la couleur demandée.
	if (sCouleurDemandee != sREG_Atout) {

		// Cas numéro 2.1 : Le joueur a la couleur demandée, il doit la jouer.
		if (bPossedeCouleurDemandee) {
			if (sCouleurJouee != sCouleurDemandee)
			{
				cout << "Carte invalide : vous devez fournir la couleur demandee (" << sCouleurDemandee << ")." << endl;
				return false;
			}
			return true;
		}

		// Cas numéro 2.2 : Le joueur n'a pas la couleur demandée mais il a de l'atout.
		if (bPossedeAtout) {
			// Le partenaire est maître, il peut jouer ce qu'il veut.
			if (bPartenaireEstMaitre) {
				return true;
			}

			// Le joueur doit couper.
			if (sCouleurJouee != sREG_Atout) {
				cout << "Carte invalide : vous devez couper a l'atout (" << sREG_Atout << ")." << endl;
				return false;
			}

			// Le joueur doit couper plus fort.
			if (bTapisCoupe) {
				unsigned int uiForceTapis = REG_ObtenirForceAtout(uiValeurMaitreTapis);
				if (uiForceAtoutMain > uiForceTapis) {
					if (REG_ObtenirForceAtout(uiValeurJouee) < uiForceTapis)
					{
						cout << "Carte invalide : vous devez monter avec un atout plus fort  (" << sREG_Atout << ")." << endl;
						return false;
					}
				}
			}
			return true;
		}
	}
	// Cas numéro 3.0 : L'atout est la couleur demandée.
	else {
		if (bPossedeAtout) {
			// Le joueur doit donner de l'atout si il a.
			if (sCouleurJouee != sREG_Atout) {
				cout << "Carte invalide :  vous devez fournir de l'atout (" << sREG_Atout << ")." << endl;
				return false;
			}

			// Obligation de monter à l'atout si on a une carte plus forte en main.
			unsigned int uiForceTapis = REG_ObtenirForceAtout(uiValeurMaitreTapis);
			if (uiForceAtoutMain > uiForceTapis) {
				if (REG_ObtenirForceAtout(uiValeurJouee) < uiForceTapis)
				{
					cout << "Carte invalide : vous devez mettre un atout plus fort que celui sur la table." << endl;
					return false;
				}
			}
			return true;
		}
	}

	// Cas numéro 4 : Le joueur n'a rien de demandé, il peut joueur ce qu'il veut.
	return true;
}

unsigned int CRegleBelote::REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli) { return 1; }; // appelle à joueur suivant + calculer points pli + ajouter 1 au pli
void CRegleBelote::REG_CalculerPointsPli() {};
void CRegleBelote::REG_CalculerPointsManche() {}; // si nécessaire



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

unsigned int CRegleBelote::REG_ObtenirForceAtout(const unsigned int& uiValeur) {
	if (uiValeur == 11) return 20;
	if (uiValeur == 9)  return 14;
	if (uiValeur == 1)  return 11;
	if (uiValeur == 10) return 10;
	if (uiValeur == 13) return 4;
	if (uiValeur == 12) return 3;
	if (uiValeur == 8)  return 2;
	if (uiValeur == 7)  return 1;
	return 0;
}

unsigned int CRegleBelote::REG_ObtenirForceNormal(const unsigned int& uiValeur) {
	if (uiValeur == 1)  return 11;
	if (uiValeur == 10) return 10;
	if (uiValeur == 13) return 4;
	if (uiValeur == 12) return 3;
	if (uiValeur == 11) return 2;
	if (uiValeur == 9)  return 0;
	if (uiValeur == 8)  return 0;
	if (uiValeur == 7)  return 0;
	return 0;
}

unsigned int CRegleBelote::REG_ObtenirMeilleurCarteTapis(const vector<unique_ptr<CCarte>>& cartesDuPli, const string& sCouleurDemandee, const string& sAtout)
{
	if (cartesDuPli.empty()) { return 0; };

	unsigned int uiIndiceMeilleurCarte = 0;
	string sMeilleurCouleur = cartesDuPli[0]->CAR_GetCouleur();
	unsigned int uiMeilleurValeur = cartesDuPli[0]->CAR_GetValeur();

	for (unsigned int uiCartePli = 1; uiCartePli < cartesDuPli.size(); uiCartePli++) {
		bool bChangementMeileurCarte = false;
		string sCouleurCourante = cartesDuPli[uiCartePli]->CAR_GetCouleur();
		unsigned int uiValeurCourante = cartesDuPli[uiCartePli]->CAR_GetValeur();

		if (sCouleurCourante == sAtout && sMeilleurCouleur != sAtout) {
			bChangementMeileurCarte = true;
		}
		else if (sCouleurCourante == sAtout && sMeilleurCouleur == sAtout) {
			if (REG_ObtenirForceAtout(uiValeurCourante) > REG_ObtenirForceAtout(uiMeilleurValeur)) {
				bChangementMeileurCarte = true;
			}
		}
		else if (sCouleurCourante == sCouleurDemandee && sMeilleurCouleur == sCouleurDemandee) {
			if (REG_ObtenirForceNormal(uiValeurCourante) > REG_ObtenirForceNormal(uiMeilleurValeur)) {
				bChangementMeileurCarte = true;
			}
		}

		if (bChangementMeileurCarte) {
			sMeilleurCouleur = sCouleurCourante;
			uiMeilleurValeur = uiValeurCourante;
			uiIndiceMeilleurCarte = uiCartePli;
		}
	}

	return uiIndiceMeilleurCarte;
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
void CRegleBelote::REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur) {};
void CRegleBelote::REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& mJEU_points) {};
void CRegleBelote::REG_AfficherAfficherPli(unique_ptr<CPaquet> pPli, vector<unsigned int> vuIdJoueurPli) {};
