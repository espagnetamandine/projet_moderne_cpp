#include "CRegleTarot.h"
#include "CPaquet.h"
#include "CJoueur.h"
#include "CCarte.h"
#include "CEquipe.h"
#include "CConsole.h"
#include "CHumain.h"

/********************************************************/
/*                    METHODES DE JEU                   */
/********************************************************/

void CRegleTarot::REG_DebutPartie(unique_ptr<CPaquet>& upPaquet, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPoints) 
{
	for (unsigned int uiBoucle = 0; uiBoucle < vuJoueurs.size(); uiBoucle++)
	{
		unique_ptr<CEquipe> upEquipe = make_unique<CEquipe>();
		upEquipe->EQU_ajouterJoueur(uiBoucle);
		upEquipe->setEQU_numeroEquipe(uiBoucle);
		muPoints[move(upEquipe)] = 0;
	}
}

bool  CRegleTarot::REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& muPoints)
{
	for (auto& equipe : muPoints)
	{
		if (equipe.second >= 500) 
		{
			return true;

		}
	}
	return false;
}

// Le chien est créer dans un prmeier temps puis le reste des cartes et distribuer aux joueurs. 
// Ensuite se met en place les enchères, soi un joueur passe  son tour ou alors il prend.
// Si un joueur prend alors selon sa mise il récupère le chien ou non, si personne ne prend alors on resdistribue les cartes.

unsigned int CRegleTarot::REG_DebutManche(unique_ptr<CPaquet>& upPaquet, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unsigned int& uiJEU_IdJoueurCourrant) 
{
	cout << "\n-------------------------------------------------" << endl;
	cout << "               Debut de la manche                 " << endl;
	cout << "--------------------------------------------------" << endl;

	// on remet toutes les cartes dans le paquet
	REG_RemettreCartesDansPaquet(vuJoueurs, upPaquet);
	
	// Si le chien n'est pas vide, on le vide.
	if(upREG_Chien != nullptr)
	{
		while (!upREG_Chien->PAQ_GetCartes().empty())
		{
			upPaquet->PAQ_AjouterCarte(upREG_Chien->PAQ_RetirerCarte());
		}
	}
	
	// mélange des cartes
	upPaquet->PAQ_Melanger();
	
	// mise en place du chien
	REG_MettreEnPlacePioche(upPaquet, vuJoueurs);
	
	// distribution des cartes restantes aux joueurs
	REG_DistribuerCartes(vuJoueurs, upPaquet);
	
	unsigned int uiAnnonceMax = 0;
	unsigned int uiIndicePreneur = 0;
	
	// mise en place des enchères
	for (unsigned int uiBoucle = 0; uiBoucle < vuJoueurs.size(); uiBoucle++) {
		if (!vuJoueurs[uiBoucle]->JOU_EstIa())
		{
			CConsole::COS_AfficherEcranSecretJoueur(vuJoueurs[uiBoucle]);
		}
		unsigned int uiChoix;
		if (!vuJoueurs[uiBoucle]->JOU_EstIa())
		{
			cout << "\nChoississez parmi les options suivantes, entrez le numero correspondant\n"
				<< " - 0 : Passer\n - 1 : Petite\n - 2 : Garde\n - 3 : Garde Sans\n - 4 : Garde Contre"
				<< "\n\nVeuillez saisir votre choix : " << endl;
			cin >> uiChoix;
			while (cin.fail())
			{
				cout << "Entree invalide, resaisissez : ";

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cin >> uiChoix;
			}
			while (uiChoix > 4 || (uiChoix > 0 && uiChoix <= uiAnnonceMax)) {
				cout << "\nEnchere invalide ou trop basse, recommencez " << endl;

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cin >> uiChoix;
			}
		}
		else
		{
			uiChoix = rand() % 5;
			while (uiChoix > 0 && uiChoix <= uiAnnonceMax) {
				uiChoix = rand() % 5;
			}
		}
		if (uiChoix > uiAnnonceMax)
		{
			uiAnnonceMax = uiChoix;
			uiIndicePreneur = uiBoucle;
		}
		switch (uiChoix) 
		{
		case 0:
			cout << "\n Le joueur " << vuJoueurs[uiBoucle]->JOU_GetNomJoueur() << " passe" << endl;
			break;
		case 1:
			cout << "\n Le joueur " << vuJoueurs[uiBoucle]->JOU_GetNomJoueur() << " choisit Petite" << endl;
			break;
		case 2:
			cout << "\n Le joueur " << vuJoueurs[uiBoucle]->JOU_GetNomJoueur() << " choisit Garde" << endl;
			break; 
		case 3:
			cout << "\n Le joueur " << vuJoueurs[uiBoucle]->JOU_GetNomJoueur() << " choisit Garde Sans" << endl;
			break;
		case 4:
			cout << "\n Le joueur " << vuJoueurs[uiBoucle]->JOU_GetNomJoueur() << " choisit Garde Contre" << endl;
			break;

		}
	}
	

	if (uiAnnonceMax == 0)
	{
		CConsole::COS_NettoyerEcran();
		cout << "\nTout le monde a passe, on redistribue.\n" << endl;
		return REG_DebutManche(upPaquet, vuJoueurs, muPointsEquipe, uiJEU_IdJoueurCourrant);
	}
	else {
		uiREG_AnnonceMax = uiAnnonceMax;
		uiREG_IndicePreneur = uiIndicePreneur;
		string sAnnonceChoix;
		switch(uiAnnonceMax)
		{
		case 1: 
			sAnnonceChoix = "Petite";
			break;
		case 2:
			sAnnonceChoix = "Garde";
			break;
		case 3:
			sAnnonceChoix = "Garde Sans";
			break;
		case 4:
			sAnnonceChoix = "Garde Contre";
			break;

		}
		CConsole::COS_NettoyerEcran();
		cout << "--------------------------------------------------" << endl;
		cout << "                Fin des contrats                  " << endl;
		cout << "--------------------------------------------------" << endl;


		cout << "\nLe joueur " << vuJoueurs[uiIndicePreneur]->JOU_GetNomJoueur() << " a pris : " << sAnnonceChoix <<" !" << endl;



		REG_ConstituerEquipes(vuJoueurs, muREG_PointsManche);

		cout << "\nAppuyez sur ENTREE des que vous etes pret a demarrer.";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();

		REG_ChoixCarteChien(vuJoueurs, uiIndicePreneur, uiAnnonceMax, muPointsEquipe);
		return uiIndicePreneur;
	}
} 


// une manche s'arrete lorsque personne n'a plus plus de cartes
bool  CRegleTarot::REG_ConditionFinManche(const vector<unique_ptr<CJoueur>>& vuJoueurs)
{
	if (vuJoueurs[0]->JOU_GetMain()->PAQ_GetCartes().size() == 0)
	{
		return true;
	}
	return false;
}

// vérification si une carte jouée  est valide ou non
// un joueur doit joueur la même couleur que la prmière carte jouée
// si ce joueur n'a pas cette couleur de carte alors il doit jouer un atout
// si ce joueur ne possède pas non plus d'atout alors il joue la carte qu'il veut
bool CRegleTarot::REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& upPaquetJoueur, const unique_ptr<CPaquet>& upPli, const vector<unsigned int>& vuIdJoueurPli)
{
	if (carte.CAR_GetNom() == "L'excuse")
	{
		return true;
	}

	if (upPli->PAQ_GetCartes().empty())
	{
		return true;
	}
	string sPossedeCouleurAJouer = upPli->PAQ_GetCartes()[0]->CAR_GetCouleur();
	bool bPossedeCouleurAJouer = false;
	bool bPossedeAtout = false;

	for (auto& carte : upPaquetJoueur->PAQ_GetCartes())
	{
		if (carte->CAR_GetCouleur() == sPossedeCouleurAJouer)
		{
			bPossedeCouleurAJouer = true;
		}
		if (carte->CAR_GetCouleur() == "Atout" && carte->CAR_GetNom() != "L'excuse")
		{
			bPossedeAtout = true;
		}
	}
	if (bPossedeCouleurAJouer)
	{
		return carte.CAR_GetCouleur() == sPossedeCouleurAJouer;
	}
	else if (bPossedeAtout)
	{
		return carte.CAR_GetCouleur() == "Atout";
	}
	else
	{
		return true;
	}
}


/********************************************************/
/*                     ENTRE - JEU                      */
/********************************************************/


// le joueur récupère le chien, et fait son paquet

void CRegleTarot::REG_ChoixCarteChien(vector<unique_ptr<CJoueur>>& vuJoueurs, unsigned uiIndicePreneur, unsigned uiAnnonceMax, map<unique_ptr<CEquipe>, int>& muPointsEquipe)
{
	switch(uiAnnonceMax)
	{
	case 1:
	case 2:
		while (!upREG_Chien-> PAQ_GetCartes().empty())
		{
			unique_ptr<CCarte> carte = upREG_Chien->PAQ_RetirerCarte();
			vuJoueurs[uiIndicePreneur]->JOU_GetMain()->PAQ_AjouterCarte(move(carte));
		}

		unsigned int uiNumEquipePreneur = 0;
		int iScoreEquipePreneur = 0;

		for (auto& equipe : muPointsEquipe) {
			vector<unsigned int> vuMembres = equipe.first->getEQU_equipe();
			if (find(vuMembres.begin(), vuMembres.end(), uiIndicePreneur) != vuMembres.end()) {
				uiNumEquipePreneur = equipe.first->getEQU_numeroEquipe();
				iScoreEquipePreneur = equipe.second;
				break;
			}
		}

		vector<unique_ptr<CCarte>>& mainJoueur = vuJoueurs[uiIndicePreneur]->JOU_GetMain()->PAQ_GetCartes();
		unsigned int uiNbCartesChien = 0;
		vector<unsigned int> vuIndicesChoisis;

		if (vuJoueurs.size() == 5)
		{
			uiNbCartesChien = 3;
		}
		else
		{
			uiNbCartesChien = 6;
		}

		if (vuJoueurs[uiIndicePreneur]->JOU_EstIa()) {
			for (int i = mainJoueur.size() - 1; i >= 0 && vuIndicesChoisis.size() < uiNbCartesChien; i--) {
				bool bEstUnBout = (mainJoueur[i]->CAR_GetCouleur() == "Atout" && (mainJoueur[i]->CAR_GetValeur() == 1 || mainJoueur[i]->CAR_GetValeur() == 21 || mainJoueur[i]->CAR_GetNom() == "L'excuse"));

				if (mainJoueur[i]->CAR_GetNom() != "Roi" && !bEstUnBout) {
					vuIndicesChoisis.push_back(i);
				}
			}
		}
		else {
			CConsole::COS_AfficherEcranSecretJoueur(vuJoueurs[uiIndicePreneur], uiNumEquipePreneur, iScoreEquipePreneur);

			cout << "Vous devez choisir " << uiNbCartesChien << " cartes dans votre main." << endl;

			for (unsigned int uiBoucle = 0; uiBoucle < uiNbCartesChien; uiBoucle++) {
				unsigned int uiIndiceCarte;
				cout << "\nChoississez un des cartes que vous voulez mettre dnas le chien : " << endl;
				cin >> uiIndiceCarte;
				while (cin.fail() ||
					uiIndiceCarte >= vuJoueurs[uiIndicePreneur]->JOU_GetMain()->PAQ_GetCartes().size() ||
					find(vuIndicesChoisis.begin(), vuIndicesChoisis.end(), uiIndiceCarte) != vuIndicesChoisis.end())
				{
					cout << "\n Choix de carte invalide, ou carte deja selectionnee, recommencez " << endl;

					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cin >> uiIndiceCarte;
				}

				vuIndicesChoisis.push_back(uiIndiceCarte);
			}
		}

		sort(vuIndicesChoisis.rbegin(), vuIndicesChoisis.rend());

		for (unsigned int uiId : vuIndicesChoisis)
		{
			unique_ptr<CCarte> carte = vuJoueurs[uiIndicePreneur]->JOU_GetMain()->PAQ_RetirerCarte(uiId);
			upREG_Chien->PAQ_AjouterCarte(move(carte));
		}

		break;
	}
	
}


// récupération du joueur qui gagne le pli
unsigned int CRegleTarot::REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli)
{
	vector<unique_ptr<CCarte>>& vcCartesPli = pPli->PAQ_GetCartes();
	unsigned int uiValeurAtoutMax = 0;
	unsigned int uiValeurCarteMax = 0;
	unsigned int uiIndiceGagnant = 0;
	for (unsigned int uiBoucle = 0; uiBoucle < vuIdJoueurPli.size(); uiBoucle++)

	{

		if (vcCartesPli[uiBoucle]->CAR_GetCouleur() == "Atout" && vcCartesPli[uiBoucle]->CAR_GetNom() != "L'excuse" && vcCartesPli[uiBoucle]->CAR_GetValeur() > uiValeurAtoutMax)
		{
			uiValeurAtoutMax = (vcCartesPli[uiBoucle]->CAR_GetValeur());
			uiIndiceGagnant = vuIdJoueurPli[uiBoucle];

		}
		else if (vcCartesPli[uiBoucle]->CAR_GetCouleur() == vcCartesPli[0]->CAR_GetCouleur() && vcCartesPli[uiBoucle]->CAR_GetNom() != "L'excuse" && vcCartesPli[uiBoucle]->CAR_GetValeur() > uiValeurCarteMax)
		{
			uiValeurCarteMax = (vcCartesPli[uiBoucle]->CAR_GetValeur());
			uiIndiceGagnant = vuIdJoueurPli[uiBoucle];
		}
	}
	return uiIndiceGagnant;

}


// calcul des points pour un pli
void CRegleTarot::REG_CalculerPointsPli(unique_ptr<CPaquet>& upPli, unsigned int uiIndiceJoueurGagnantPli, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unique_ptr<CPaquet>& upDefausse, const vector<unique_ptr<CJoueur>>& vuJoueurs)
{
	int* iPointsEquipeGagnante = nullptr;

	for (auto& equipe : muREG_PointsManche)
	{
		equipe.first;
		equipe.second;
		vector<unsigned int> vuEquipe = equipe.first->getEQU_equipe();
		if (find(vuEquipe.begin(), vuEquipe.end(), uiIndiceJoueurGagnantPli) != vuEquipe.end())
		{
			iPointsEquipeGagnante = &equipe.second;
		}
	}
	if (iPointsEquipeGagnante == nullptr) {
		cout << "ERREUR: equipe gagnante non trouvee pour le joueur " << uiIndiceJoueurGagnantPli << endl;
		return;
	}
	// les valeurs *2 de chaque cartes
	for (unsigned int uiBoucle = 0; uiBoucle < upPli->PAQ_GetCartes().size(); uiBoucle++)
	{
		if (upPli->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() == "Roi" || (upPli->PAQ_GetCartes()[uiBoucle]->CAR_GetCouleur() == "Atout" && (upPli->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur() == 1 || upPli->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur() == 21)))
		{
			*iPointsEquipeGagnante += 9;
		}
		else if (upPli->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() == "L'excuse")
		{
			*iPointsEquipeGagnante += 9;
		}
		else if (upPli->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() == "Dame")
		{
			*iPointsEquipeGagnante += 7;
		}
		else if (upPli->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() == "Cavalier")
		{
			*iPointsEquipeGagnante += 5;
		}
		else if (upPli->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() == "Valet")
		{
			*iPointsEquipeGagnante += 3;
		}
		else
		{
			*iPointsEquipeGagnante += 1;
		}
	}
	while (!upPli->PAQ_GetCartes().empty()) {
		upDefausse->PAQ_AjouterCarte(upPli->PAQ_RetirerCarte());
	}
}

// calcul des points d'une manche des joueurs
void CRegleTarot::REG_CalculerPointsManche(unique_ptr<CPaquet>& upPli, unsigned int uiIndiceJoueurGagnant, map<unique_ptr<CEquipe>, int>& muPointsEquipe, unique_ptr<CPaquet>& upDefausse, const vector<unique_ptr<CJoueur>>& vuJoueurs)
{
	unsigned int uiNbBouts = 0;

	for (unsigned int uiBoucle = 0; uiBoucle < upREG_Chien->PAQ_GetCartes().size(); uiBoucle++)
	{
		if (upREG_Chien->PAQ_GetCartes()[uiBoucle]->CAR_GetCouleur() == "Atout" && (upREG_Chien->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur() == 1 || upREG_Chien->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur() == 21 || upREG_Chien->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() == "L'excuse"))
		{
			uiNbBouts++;
		}
	}
	for (unsigned int uiBoucle = 0; uiBoucle < upDefausse->PAQ_GetCartes().size(); uiBoucle++)
	{
		if (upDefausse->PAQ_GetCartes()[uiBoucle]->CAR_GetCouleur() == "Atout" && (upDefausse->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur() == 1 || upDefausse->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur() == 21 || upDefausse->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() == "L'excuse"))
		{
			uiNbBouts++;
		}
	}
	// seuil de victoires selon le nombre de bout que possède le preneur dans les plis qu'il a gagné à la fin de la partie
	unsigned int uiSeuilVictoire;
	switch (uiNbBouts)
	{
	case 0:
		uiSeuilVictoire = 56;
		break;
	case 1:
		uiSeuilVictoire = 51;
		break;
	case 2:
		uiSeuilVictoire = 41;
		break;
	case 3:
		uiSeuilVictoire = 36;
		break;
	}
	for (unsigned int uiBoucle = 0; uiBoucle < upPli->PAQ_GetCartes().size(); uiBoucle++)
	{

		// si le petit est joué à la fin de partie, alors si le preneur remporte ce pli, il remporte 10 points bonus
		// au contraire s'il perd alors il prend 10 points de malus
		if (upPli->PAQ_GetCartes()[uiBoucle]->CAR_GetCouleur() == "Atout" && upPli->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur() == 1)
		{
			for (auto& equipe : muREG_PointsManche) {

				vector<unsigned int> vuEquipe = equipe.first->getEQU_equipe();
				if (find(vuEquipe.begin(), vuEquipe.end(), uiREG_IndicePreneur) != vuEquipe.end())
				{
					if (find(vuEquipe.begin(), vuEquipe.end(), uiIndiceJoueurGagnant) != vuEquipe.end())
					{
						equipe.second += 10;
					}
					else
					{
						equipe.second -= 10;
					}
				}
			}
		}
	}
	int iPointsPreneur = 0;
	for (auto& equipe : muREG_PointsManche) {
		vector<unsigned int> vuEquipe = equipe.first->getEQU_equipe();
		if (find(vuEquipe.begin(), vuEquipe.end(), uiREG_IndicePreneur) != vuEquipe.end())
		{
			iPointsPreneur = equipe.second;
		}
	}

	// différents multiplicateurs selon la mise aux enchères au début de de la partie
	unsigned int uiMultiplicateur = 1;
	switch (uiREG_AnnonceMax)
	{
	case 1:
		uiMultiplicateur = 1;
		break;
	case 2:
		uiMultiplicateur = 2;
		break;
	case 3:
		uiMultiplicateur = 4;
		break;
	case 4:
		uiMultiplicateur = 6;
		break;
	default:
		uiMultiplicateur = 1;
		break;
	}
	// calcul des points
	for (auto& equipeIndividuelle : muPointsEquipe) {
		unsigned int uiJoueur = equipeIndividuelle.first->getEQU_equipe()[0];
		bool bJoueurEstPreneur = (uiJoueur == uiREG_IndicePreneur);

		int iEcartReel = (int)iPointsPreneur - (int)(uiSeuilVictoire * 2);
		int iScoreManche = (25 * 2 + abs(iEcartReel)) * uiMultiplicateur;

		bool bContratRempli = ((int)iPointsPreneur >= (int)uiSeuilVictoire * 2);

		// si le joueur est dans la même équipe que le prenneur pour la manche
		bool bJoueurEstDansCampPreneur = false;
		for (auto& equipeManche : muREG_PointsManche) {
			vector<unsigned int> vuMembres = equipeManche.first->getEQU_equipe();
			if (find(vuMembres.begin(), vuMembres.end(), uiREG_IndicePreneur) != vuMembres.end() &&
				find(vuMembres.begin(), vuMembres.end(), uiJoueur) != vuMembres.end()) {
				bJoueurEstDansCampPreneur = true;
				break;
			}
		}

		if (bContratRempli)
		{
			if (bJoueurEstDansCampPreneur)
			{
				if (uiJoueur == uiREG_IndicePreneur) {
					equipeIndividuelle.second += iScoreManche * (vuJoueurs.size() - 1);
				}
				else {
					equipeIndividuelle.second += iScoreManche;
				}
			}
			else
			{
				equipeIndividuelle.second -= iScoreManche; // Défenseur
			}
		}
		else
		{
			if (bJoueurEstDansCampPreneur)
			{
				if (uiJoueur == uiREG_IndicePreneur) {
					equipeIndividuelle.second -= iScoreManche * (vuJoueurs.size() - 1);
				}
				else {
					equipeIndividuelle.second -= iScoreManche;
				}
			}
			else
			{
				equipeIndividuelle.second += iScoreManche;
			}
		}
	}
	REG_AfficherGagnantManche(muPointsEquipe, vuJoueurs);
	REG_AfficherPoints(muPointsEquipe,vuJoueurs);

}

/********************************************************/
/*                    MISES EN PLACE                    */
/********************************************************/


// le tarot se joue de 3 à 5 joueurs
bool CRegleTarot::REG_VerificationNbJoueur(unsigned int uiNbJoueurs)
{
	if (uiNbJoueurs == 3 || uiNbJoueurs == 4 || uiNbJoueurs == 5)
	{
		return true;
	}
	return false;
}


// si une partie contient 5 joueurs, alors la partie se déroule en deux équipes
// l'équipe des défenseurs contient 3 joueurs et l'équipe des preneurs contient 2 joueurs où c'est le preneur qui va choisir son coéquipier en appelant un roi qui ne possede pas
// si le preneur possède tous les rois, alors il joue tout seul contre 4 personnes, et de même s'il appelle un roi qui est dans le chien
// si une partie se déroule à 3 ou 4 joueurs alors le preneur joue tout seul contre les autres joueurs
void CRegleTarot::REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe)
{
	unique_ptr<CEquipe> pEquipePreneur = make_unique<CEquipe>();
	unique_ptr<CEquipe> pEquipeDefenseurs = make_unique<CEquipe>();
	pEquipePreneur->EQU_ajouterJoueur(uiREG_IndicePreneur);
	if (vuJoueurs.size() == 5)
	{
		unsigned int uiNbRois = 0;
		for (auto& carte : vuJoueurs[uiREG_IndicePreneur]-> JOU_GetMain()->PAQ_GetCartes())
		{
			
			if (carte->CAR_GetNom()== "Roi")
			{
				uiNbRois++;
			}
		}
		if (uiNbRois ==4)
		{
			for (unsigned int uiBoucle= 0; uiBoucle < vuJoueurs.size(); uiBoucle++)
			{
				if (uiBoucle != uiREG_IndicePreneur)
				{
					pEquipeDefenseurs->EQU_ajouterJoueur(uiBoucle);
				}
			}
		}
		else {
			string sCouleurChoisie;
			
			if(!vuJoueurs[uiREG_IndicePreneur]->JOU_EstIa())
			{
				cout << "\n Le joueur " << vuJoueurs[uiREG_IndicePreneur]->JOU_GetNomJoueur() << " appelle le Roi de : " << endl;
				cin >> sCouleurChoisie;
				while (cin.fail() || sCouleurChoisie != "Coeur" && sCouleurChoisie != "Trefle" && sCouleurChoisie != "Carreau" && sCouleurChoisie != "Pique")
				{
					cout << "\n Couleur invalide, recommencez : " << endl;
					cin >> sCouleurChoisie;
				}
			}
			else
			{
				// Logique IA : l'IA appelle une couleur au hasard parmi les 4 enseignes de base
				vector<string> vsCouleurs = { "Coeur", "Trefle", "Carreau", "Pique" };
				sCouleurChoisie = vsCouleurs[rand() % 4];
				cout << "\n Le joueur " << vuJoueurs[uiREG_IndicePreneur]->JOU_GetNomJoueur() << " appelle le Roi de " << sCouleurChoisie << " !" << endl;
			}
			for (unsigned int uiBoucle = 0; uiBoucle < vuJoueurs.size(); uiBoucle++)
			{
				if (uiBoucle != uiREG_IndicePreneur)
				{
					bool bPossedeLeRoi = false ;
					for (auto& carte : vuJoueurs[uiBoucle]->JOU_GetMain()->PAQ_GetCartes())
					{
						if (carte->CAR_GetNom() == "Roi" && carte->CAR_GetCouleur()== sCouleurChoisie)
						{
							bPossedeLeRoi = true;
						}
						
					}
					if (bPossedeLeRoi == true) {
						pEquipePreneur->EQU_ajouterJoueur(uiBoucle);
					}
					else {
						pEquipeDefenseurs->EQU_ajouterJoueur(uiBoucle);
					}
				}
			}

		}
		

	}
	else
	{
		for (unsigned int uiBoucle = 0; uiBoucle < vuJoueurs.size(); uiBoucle++)
		{
			if (uiBoucle != uiREG_IndicePreneur) {
				pEquipeDefenseurs->EQU_ajouterJoueur(uiBoucle);
			}
		}
	}
	muPointsEquipe[move(pEquipePreneur)] = 0;
	muPointsEquipe[move(pEquipeDefenseurs)] = 0;
}

// mise en plzce du chien
void CRegleTarot::REG_MettreEnPlacePioche(unique_ptr<CPaquet>& upPaquet, vector<unique_ptr<CJoueur>>& vuJoueurs)
{

	upREG_Chien = CPaquetManager::PAQ_CreerPaquet("Joueur");
	unsigned int uiNbCartesChien = 0;
	// s'il y a 5 joueurs, alors le chien contient 3 cartes
	if (vuJoueurs.size() == 5)
	{
		uiNbCartesChien = 3;
	}
	// sinon le chien contient 6 cartes
	else
	{
		uiNbCartesChien = 6;
	}
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbCartesChien; uiBoucle++)
	{
		unique_ptr<CCarte> upCarte = upPaquet->PAQ_RetirerCarte();
		upREG_Chien->PAQ_AjouterCarte(move(upCarte));
	}

}



// distribution des cartes
void CRegleTarot:: REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& vuJoueurs, unique_ptr<CPaquet>& upPaquet) 
{
	
	// on distribue les cartes 3 par 3
	for (unsigned int uiBoucle = 0; uiBoucle < (((upPaquet->PAQ_GetCartes().size()) / vuJoueurs.size())/3); uiBoucle++) 
	{
		for (auto& joueur: vuJoueurs) 
		{
			for (unsigned int uiBoucle2 = 0; uiBoucle2 < 3; uiBoucle2++)
			{
				unique_ptr<CCarte> carte = upPaquet->PAQ_RetirerCarte();
				joueur->JOU_GetMain()->PAQ_AjouterCarte(move(carte));
			}
			
		}
	}
}

// à la fin d'une manche on remet les cartes dans le paquet
void CRegleTarot::REG_RemettreCartesDansPaquet(vector<unique_ptr<CJoueur>>& vuJoueurs, unique_ptr<CPaquet>& upPaquetPrincipal) {
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
 
// première carte joué d'un pli
bool CRegleTarot::REG_PremiereCarte(CCarte& carte) {
	return true;
}

/********************************************************/
/*                       AFFICHAGE                      */
/********************************************************/

// affichage du gagnant d'un pli
void CRegleTarot::REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>& vuJoueurs, unsigned int uiIndiceJoueurGagnantPli)
{
	cout << "--------------------------------------------------" << endl;
	cout << "                  Fin du pli                      " << endl;
	cout << "--------------------------------------------------\n" << endl;

	cout << "\n Le joueur " << vuJoueurs[uiIndiceJoueurGagnantPli]->JOU_GetNomJoueur() << " remporte le pli !" << endl;
}

void CRegleTarot::REG_AfficherGagnantManche(map<unique_ptr<CEquipe>, int>& muPointsEquipe, const vector<unique_ptr<CJoueur>>& vuJoueurs)
{
	cout << "--------------------------------------------------" << endl;
	cout << "               Fin de la manche                   " << endl;
	cout << "--------------------------------------------------\n" << endl;

	auto it = muPointsEquipe.begin();
	int iPointsMax = it->second;

	CEquipe* pEquipeGagnante = it->first.get();

	for (auto& equipe : muPointsEquipe) {

		if (equipe.second > iPointsMax)
		{
			iPointsMax = equipe.second;
			pEquipeGagnante = equipe.first.get();
		}
	}
	cout << "\n Les joueurs qui remportent la manche sont: " << endl;
	for (unsigned int uiBoucle : pEquipeGagnante->getEQU_equipe())
	{
		cout << vuJoueurs[uiBoucle]->JOU_GetNomJoueur() << endl;
	}
}


// affichage final du gagnant de la partie
void CRegleTarot::REG_AfficherGagnantPartie(map<unique_ptr<CEquipe>, int>& muPoints, const vector<unique_ptr<CJoueur>>& vuJoueurs)
{
	int iPointsMax = 0;
	CEquipe* pEquipeGagnante = nullptr;
	for (auto& equipe: muPoints)
	{
		if (equipe.second > iPointsMax)
		{
			iPointsMax = equipe.second;
			pEquipeGagnante = equipe.first.get();
		}
	}

	if (pEquipeGagnante != nullptr)
	{
		vector<string> vsNomsGagnants;

		for (unsigned int uiIdJoueur : pEquipeGagnante->getEQU_equipe())
		{
			vsNomsGagnants.push_back(vuJoueurs[uiIdJoueur]->JOU_GetNomJoueur());
		}

		CConsole::COS_AfficherGagnants(vsNomsGagnants);
	}
}

void CRegleTarot::REG_AfficherMainJoueur(unsigned int uiIdJoueur, vector<unique_ptr<CJoueur>>& vuJoueurs, map<unique_ptr<CEquipe>, int>& muPointsEquipe)
{
	for (unsigned int uiBoucle = 0; uiBoucle < vuJoueurs[uiIdJoueur]->JOU_GetMain()->PAQ_GetCartes().size(); uiBoucle++)
	{
		cout << "Carte " << uiBoucle << " : " << *vuJoueurs[uiIdJoueur]->JOU_GetMain()->PAQ_GetCartes()[uiBoucle] << endl;
	}

} 
// affichage des points
void CRegleTarot::REG_AfficherPoints(map<unique_ptr<CEquipe>, int>& muPoints, const vector<unique_ptr<CJoueur>>& vuJoueurs)
{
	for (auto& equipe : muPoints)
	{
		unsigned int uiJoueur = equipe.first->getEQU_equipe()[0];
		cout << "\n " << (vuJoueurs)[uiJoueur]->JOU_GetNomJoueur() << " : " << equipe.second << " points" << endl;
	}
}

/********************************************************/
/*                    NON - UTILISEES                   */
/********************************************************/

void CRegleTarot::REG_AfficherAfficherPli(unique_ptr<CPaquet>& upPli, vector<unsigned int> vuIdJoueurPli){}
