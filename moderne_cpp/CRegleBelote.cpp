#include "CRegleBelote.h"
#include "CPaquet.h"
#include "CJoueur.h"
#include "CCarte.h"
#include "CEquipe.h"
#include "CConsole.h"

using namespace std;

/********************************************************/
/*                  SETTERS ET GETTERS                  */
/********************************************************/

void CRegleBelote::REG_SetAtout(string sNouveauAtout) { sREG_Atout = sNouveauAtout; }

/********************************************************/
/*                    METHODES DE JEU                   */
/********************************************************/

void CRegleBelote::REG_DebutPartie(unique_ptr<CPaquet>& upPaquetPrincipal, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe){
    if (upPaquetPrincipal != nullptr) {
		upPaquetPrincipal->PAQ_Melanger();
    }

    REG_ConstituerEquipes(vuJoueurs, muPointsEquipe);
};

bool CRegleBelote::REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& muPointsEquipe) {
	for (auto it = muPointsEquipe.begin(); it != muPointsEquipe.end(); ++it)
	{
		int iScoreEquipe = it->second;

		if (iScoreEquipe >= 200) // À changer à 1000 plus tard
		{
			return true;
		}
	}

	return false;
}

unsigned int CRegleBelote::REG_DebutManche(unique_ptr<CPaquet>& upPaquetPrincipal, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unsigned int& uiIdJoueurCourrant)
{
	cout << "Faites ENTREE une fois que tout le monde peut commencer pour lancer la manche.\n";
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	CConsole::COS_NettoyerEcran();

	////////////////////////
	// DEBUT DE LA MANCHE //
	////////////////////////
	
	// Distribution (je n'ai pas fait 3 puis 2 vu qu'ici je mélange le paquet, je ne le coupe pas)
	sREG_Atout = "";
	REG_DistribuerCartes(vuJoueurs, upPaquetPrincipal);

	// Carte du milieu qu'on retourne
	unique_ptr<CCarte> pcCarteDuMilieu = upPaquetPrincipal->PAQ_RetirerCarte();

	// Enchere du premier tour pour savoir quel joueur prend
	int iJoueurPreneur = REG_PremierTourEnchere(vuJoueurs, uiIdJoueurCourrant, *pcCarteDuMilieu, muPointsEquipe);

	if (iJoueurPreneur == -1) {
		// Enchere du deuxieme tour pour savoir quel joueur prend a quoi
		iJoueurPreneur = REG_DeuxiemeTourEnchere(vuJoueurs, uiIdJoueurCourrant, pcCarteDuMilieu->CAR_GetCouleur(), muPointsEquipe);
	}

	// Si personne n'a voulu prendre après les deux tours
	if (iJoueurPreneur == -1) {
		upPaquetPrincipal->PAQ_AjouterCarte(move(pcCarteDuMilieu));
		REG_RemettreCartesDansPaquet(vuJoueurs, upPaquetPrincipal);
		uiIdJoueurCourrant = (uiIdJoueurCourrant + 1) % vuJoueurs.size();

		CConsole::COS_NettoyerEcran();

		cout << "Les cartes ont été remises dans le paquet, on relance la manche.\n";
		return REG_DebutManche(upPaquetPrincipal, vuJoueurs, muPointsEquipe, uiIdJoueurCourrant);
	}


	CConsole::COS_NettoyerEcran();

	cout << "--------------------------------------------------" << endl;
	cout << "               Debut de la manche                 " << endl;
	cout << "--------------------------------------------------" << endl;

	cout << "\nLa manche peut commencer !" << endl;
	cout << vuJoueurs[iJoueurPreneur]->JOU_GetNomJoueur() << " a pris. L'atout est : " << sREG_Atout << endl;

	// Distribution du reste des cartes
	for (size_t sBoucleJoueur = 0; sBoucleJoueur < vuJoueurs.size(); ++sBoucleJoueur) {
		if (sBoucleJoueur == iJoueurPreneur) {
			vuJoueurs[sBoucleJoueur]->JOU_GetMain()->PAQ_AjouterCarte(move(pcCarteDuMilieu));
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
			vuJoueurs[sBoucleJoueur]->JOU_GetMain()->PAQ_AjouterCarte(upPaquetPrincipal->PAQ_RetirerCarte());
		}
	}
	cout << "Distribution terminee. Tous les joueurs ont 8 cartes." << endl;

	cout << "\nAppuyez sur ENTREE des que vous etes pret a demarrer.";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	CConsole::COS_NettoyerEcran();

	return uiIdJoueurCourrant;
}

bool CRegleBelote::REG_ConditionFinManche(const vector<unique_ptr<CJoueur>>& vuJoueurs) {
	for (unsigned int uiBoucleJoueur = 0; uiBoucleJoueur < vuJoueurs.size(); uiBoucleJoueur++){
		if (!vuJoueurs[uiBoucleJoueur]->JOU_GetMain()->PAQ_GetCartes().empty()) {
			return false;
		}
	}
	return true;
};

bool CRegleBelote::REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& upPaquetJoueur, const unique_ptr<CPaquet>& upPli, const vector<unsigned int>& vuIdJoueurPli)
{
	vector<unique_ptr<CCarte>>& cartesDuPli = upPli->PAQ_GetCartes();
	vector<unique_ptr<CCarte>>& mainJoueur = upPaquetJoueur->PAQ_GetCartes();

	// Cas numéro 1 : Le pli est vide, tout est autorisé.
	if (cartesDuPli.empty() || vuIdJoueurPli.empty()) {
		return true;
	}

	string sCouleurDemandee = cartesDuPli[0]->CAR_GetCouleur();
	string sCouleurJouee = carte.CAR_GetCouleur();
	unsigned int uiValeurJouee = carte.CAR_GetValeur();

	// Infos de la main du joueur //
	bool bPossedeCouleurDemandee = false;
	bool bPossedeAtout = false;
	unsigned int uiForceAtoutMain = 0;

	for (unsigned int uiBoucleCarte = 0; uiBoucleCarte < mainJoueur.size(); uiBoucleCarte++) {
		if (mainJoueur[uiBoucleCarte]->CAR_GetCouleur() == sCouleurDemandee) {
			bPossedeCouleurDemandee = true;
		}
		if (mainJoueur[uiBoucleCarte]->CAR_GetCouleur() == sREG_Atout) {
			bPossedeAtout = true;
			unsigned int uiForce = REG_ObtenirForceAtout(mainJoueur[uiBoucleCarte]->CAR_GetValeur());
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

/********************************************************/
/*                     ENTRE - JEU                      */
/********************************************************/

unsigned int CRegleBelote::REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& upPli, vector<unsigned int>& vuIdJoueurPli) {
	const vector<unique_ptr<CCarte>>& cartesDuPli = upPli->PAQ_GetCartes();

	if (cartesDuPli.empty() || vuIdJoueurPli.empty()) {
		return 0;
	}

	string sCouleurDemandee = cartesDuPli[0]->CAR_GetCouleur();

	unsigned int uiIdxMeilleureCarte = REG_ObtenirMeilleurCarteTapis(cartesDuPli, sCouleurDemandee, sREG_Atout);

	return vuIdJoueurPli[uiIdxMeilleureCarte];
};

void CRegleBelote::REG_CalculerPointsPli(unique_ptr<CPaquet>& upPli, unsigned int uiIndiceJoueurGagnantPli, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unique_ptr<CPaquet>& upDefausse) {
	vector<unique_ptr<CCarte>>& cartesDuPli = upPli->PAQ_GetCartes();
	unsigned int uiTotalPointsPli = 0;

	for (unsigned int uiBoucleCarte = 0; uiBoucleCarte < cartesDuPli.size(); uiBoucleCarte++) {
		unsigned int uiValeur = cartesDuPli[uiBoucleCarte]->CAR_GetValeur();

		if (cartesDuPli[uiBoucleCarte]->CAR_GetCouleur() == sREG_Atout) {
			uiTotalPointsPli += REG_ObtenirForceAtout(uiValeur);
		}
		else {
			uiTotalPointsPli += REG_ObtenirForceNormal(uiValeur);
		}
	}

	unsigned int uiNumEquipeGagnante = 0;
	for (auto it = muPointsEquipe.begin(); it != muPointsEquipe.end(); ++it) {
		vector<unsigned int> vuMembres = it->first->getEQU_equipe();
		for (unsigned int id : vuMembres) {
			if (id == uiIndiceJoueurGagnantPli) {
				uiNumEquipeGagnante = it->first->getEQU_numeroEquipe();
				break;
			}
		}
	}

	if (uiNumEquipeGagnante == 1) {
		iREG_PointsMancheEquipe1 += uiTotalPointsPli;
	}
	else if (uiNumEquipeGagnante == 2) {
		iREG_PointsMancheEquipe2 += uiTotalPointsPli;
	}

	while (!cartesDuPli.empty()) {
		upDefausse->PAQ_AjouterCarte(move(cartesDuPli.back()));
		cartesDuPli.pop_back();
	}
}

void CRegleBelote::REG_CalculerPointsManche(unique_ptr<CPaquet>& upPli, unsigned int uiIndiceJoueurGagnantPli, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unique_ptr<CPaquet>& upDefausse, const vector<unique_ptr<CJoueur>>& vuJoueurs) {
	int* piPointsPreneurs = nullptr;
	int* piPointsDefenseurs = nullptr;

	if (uiREG_NumeroEquipePreneuse == 1) {
		piPointsPreneurs = &iREG_PointsMancheEquipe1;
		piPointsDefenseurs = &iREG_PointsMancheEquipe2;
	}
	else {
		piPointsPreneurs = &iREG_PointsMancheEquipe2;
		piPointsDefenseurs = &iREG_PointsMancheEquipe1;
	}

	int iTotalPointsManche = iREG_PointsMancheEquipe1 + iREG_PointsMancheEquipe2;

	if (*piPointsPreneurs <= *piPointsDefenseurs) {
		*piPointsPreneurs = 0;
		*piPointsDefenseurs = iTotalPointsManche; // L'équipe est dedans elle donne tout les points
	}
	else if (*piPointsDefenseurs == 0) {
		*piPointsPreneurs = 250; // L'équipe adverse est capot.
	}

	for (auto it = muPointsEquipe.begin(); it != muPointsEquipe.end(); ++it) {
		if (it->first->getEQU_numeroEquipe() == 1) {
			it->second += iREG_PointsMancheEquipe1;
		}
		else if (it->first->getEQU_numeroEquipe() == 2) {
			it->second += iREG_PointsMancheEquipe2;
		}
	}

	REG_AfficherGagnantManche(muPointsEquipe, vuJoueurs);
};

/********************************************************/
/*                    MISES EN PLACE                    */
/********************************************************/

bool CRegleBelote::REG_VerificationNbJoueur(unsigned int uiNbJoueurs) {
	if (uiNbJoueurs == 4)
	{
		return true;
	}

	return false;
}

void CRegleBelote::REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe)
{
	if (vuJoueurs.size() == 4)
	{
		vector<unsigned int> uiNumerosJoueursUne = { 0, 2 };
		vector<unsigned int> uiNumerosJoueursDeux = { 1, 3 };

		unique_ptr<CEquipe> peEquipeUne = make_unique<CEquipe>(uiNumerosJoueursUne, 1);
		unique_ptr<CEquipe> peEquipeDeux = make_unique<CEquipe>(uiNumerosJoueursDeux, 2);

		muPointsEquipe.emplace(move(peEquipeUne), 0);
		muPointsEquipe.emplace(move(peEquipeDeux), 0);

		cout << "Voici les equipes creees :" << endl;
		cout << " -> Equipe 1 : " << vuJoueurs[0]->JOU_GetNomJoueur() << " & " << vuJoueurs[2]->JOU_GetNomJoueur() << endl;
		cout << " -> Equipe 2 : " << vuJoueurs[1]->JOU_GetNomJoueur() << " & " << vuJoueurs[3]->JOU_GetNomJoueur() << endl;
	}
}

void CRegleBelote::REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& vuJoueurs, unique_ptr<CPaquet>& upPaquetPrincipal) {
	unsigned int uiBoucleCarte;

	for (unique_ptr<CJoueur>& joueur : vuJoueurs) {
		joueur->JOU_GetMain()->PAQ_GetCartes().clear();
	}

	upPaquetPrincipal->PAQ_Melanger();

	for (uiBoucleCarte = 0; uiBoucleCarte < 5; uiBoucleCarte++)
	{
		for (unique_ptr<CJoueur>& joueur : vuJoueurs) {
			joueur->JOU_GetMain()->PAQ_AjouterCarte(upPaquetPrincipal->PAQ_RetirerCarte());
		}
	}
};

void CRegleBelote::REG_RemettreCartesDansPaquet(vector<unique_ptr<CJoueur>>& vuJoueurs, unique_ptr<CPaquet>& upPaquetPrincipal) {
	for (unique_ptr<CJoueur>& joueur : vuJoueurs) {
		vector<unique_ptr<CCarte>>& mainJoueur = joueur->JOU_GetMain()->PAQ_GetCartes();

		while (!mainJoueur.empty()) {
			upPaquetPrincipal->PAQ_AjouterCarte(move(mainJoueur.back()));
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
			REG_AfficherMainJoueur(uiJoueurQuiParle, joueurs, points);

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
			for (auto it = points.begin(); it != points.end(); ++it) {
				for (unsigned int id : it->first->getEQU_equipe()) {
					if (id == uiJoueurQuiParle) {
						uiREG_NumeroEquipePreneuse = it->first->getEQU_numeroEquipe();
						break;
					}
				}
			}
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
			REG_AfficherMainJoueur(uiJoueurQuiParle, joueurs, points);

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
			for (auto it = points.begin(); it != points.end(); ++it) {
				for (unsigned int id : it->first->getEQU_equipe()) {
					if (id == uiJoueurQuiParle) {
						uiREG_NumeroEquipePreneuse = it->first->getEQU_numeroEquipe();
						break;
					}
				}
			}
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

void CRegleBelote::REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vuJoueurs, unsigned int uiIndiceJoueurGagnantPli) {
	cout << "--------------------------------------------------" << endl;
	cout << "                  Fin du pli                      " << endl;
	cout << "--------------------------------------------------\n" << endl;

	cout << "Le pli est remporte par : " << vuJoueurs[uiIndiceJoueurGagnantPli]->JOU_GetNomJoueur() << " !\n" << endl;
};

void CRegleBelote::REG_AfficherGagnantManche(map<unique_ptr<CEquipe>, int>& muPointsEquipe, const vector<unique_ptr<CJoueur>>& vuJoueurs)
{
	cout << "--------------------------------------------------" << endl;
	cout << "               Fin de la manche                   " << endl;
	cout << "--------------------------------------------------\n" << endl;

	cout << "Nombre de points recuperees par chaque equipe :" << endl;
	cout << " -> Equipe 1 : " << iREG_PointsMancheEquipe1 << " points." << endl;
	cout << " -> Equipe 2 : " << iREG_PointsMancheEquipe2 << " points.\n" << endl;

	cout << "\nScores generaux de la partie : " << endl;

	for (auto it = muPointsEquipe.begin(); it != muPointsEquipe.end(); ++it) {
		unsigned int uiNumEquipe = it->first->getEQU_numeroEquipe();
		int iScoreTotal = it->second;

		vector<unsigned int> vuMembres = it->first->getEQU_equipe();

		string sNomsMembres = "";
		for (unsigned int uiBoucleJoueur = 0; uiBoucleJoueur < vuMembres.size(); uiBoucleJoueur++) {
			unsigned int idJoueur = vuMembres[uiBoucleJoueur];
			if (idJoueur < vuJoueurs.size()) {
				sNomsMembres += vuJoueurs[idJoueur]->JOU_GetNomJoueur();
				if (uiBoucleJoueur < vuMembres.size() - 1) {
					sNomsMembres += " & ";
				}
			}
		}

		cout << " -> Equipe " << uiNumEquipe << " (" << sNomsMembres << ") : " << iScoreTotal << " points." << endl;
	}

	cout << "\n\nAppuyez sur ENTREE pour passer a la manche suivante...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}

void CRegleBelote::REG_AfficherGagnantPartie(map<unique_ptr<CEquipe>, int>& muPointsEquipe, const vector<unique_ptr<CJoueur>>& vuJoueurs) {
	for (auto it = muPointsEquipe.begin(); it != muPointsEquipe.end(); ++it)
	{
		int iScoreEquipe = it->second;

		if (iScoreEquipe >= 200)
		{
			vector<unsigned int> vuIdsMembres = it->first->getEQU_equipe();

			vector<string> vsNomsGagnants;
			for (unsigned int id : vuIdsMembres) {
				if (id < vuJoueurs.size()) {
					vsNomsGagnants.push_back(vuJoueurs[id]->JOU_GetNomJoueur());
				}
			}

			string sNomEquipe = "Equipe " + to_string(it->first->getEQU_numeroEquipe());

			CConsole::COS_AfficherGagnants(vsNomsGagnants, sNomEquipe);

			break;
		}
	}
};

void CRegleBelote::REG_AfficherMainJoueur(unsigned int uiIdJoueur, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe) {
	unsigned int uiNumEquipe = 0;
	int iScoreEquipe = 0;

	for (auto it = muPointsEquipe.begin(); it != muPointsEquipe.end(); ++it) {
		vector<unsigned int> vNumeros = it->first->getEQU_equipe();
		for (unsigned int num : vNumeros) {
			if (num == uiIdJoueur) {
				uiNumEquipe = it->first->getEQU_numeroEquipe();
				iScoreEquipe = it->second;
				break;
			}
		}
	}

	CConsole::COS_AfficherEcranSecretJoueur(vuJoueurs[uiIdJoueur], uiNumEquipe, iScoreEquipe);
}

/********************************************************/
/*                    NON - UTILISEES                   */
/********************************************************/

void CRegleBelote::REG_MettreEnPlacePioche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs) {};

void CRegleBelote::REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& mJEU_points) {};
void CRegleBelote::REG_AfficherAfficherPli(unique_ptr<CPaquet>& upPli, vector<unsigned int> vuIdJoueurPli) {};
