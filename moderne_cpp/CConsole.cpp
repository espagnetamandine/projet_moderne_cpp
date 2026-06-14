#include "CConsole.h"

using namespace std;

void CConsole::COS_ChoisirJeu()
{
	unsigned int uiBoucle, uiChoixJeu;
	cout << "A quoi souhaitez-vous jouer ?" << endl;
	cout << "-----------------------------\n" << endl;

	for (uiBoucle = 0; uiBoucle < vsCOS_listeJeu.size(); uiBoucle++)
	{
		cout << "Choix n°" << uiBoucle + 1 << " : " << vsCOS_listeJeu[uiBoucle] << endl;
	}

	cout << "0 : Fermer l'application\n" << endl;

	cout << "Veuillez selectionner votre choix : ";
	cin >> uiChoixJeu;

	while (cin.fail() || uiChoixJeu > vsCOS_listeJeu.size())
	{
		cout << "ERREUR : Choix invalide. Veuillez reselectionner votre choix : ";

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cin >> uiChoixJeu;
	}
	if (uiChoixJeu > 0)
	{
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		unique_ptr<CJeu> pjJeuALancer = make_unique<CJeu>(vsCOS_listeJeu[uiChoixJeu - 1]);
		COS_PreparerJeu(move(pjJeuALancer));
	}
}

void CConsole::COS_PreparerJeu(unique_ptr<CJeu> pjJeuALancer)
{
	COS_NettoyerEcran();
	unsigned int uiNbJoueur, uiNbHumain, uiBoucle;

	cout << "----------------------------------------------------------" << endl;
	cout << "Preparation du jeu : " << GRAS << pjJeuALancer->JEU_GetNom() << RESET << endl;
	cout << "----------------------------------------------------------\n" << endl;

	cout << "A combien de joueurs souhaitez vous jouer ? : ";
	cin >> uiNbJoueur;

	while (cin.fail() || !pjJeuALancer->JEU_SetNombreJoueur(uiNbJoueur))
	{
		cout << "ERREUR : Nombre de joueur impossible pour ce jeu. Veuillez resaisir : ";

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cin >> uiNbJoueur;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "\n\nVous etes " << uiNbJoueur << " a jouer !" << endl;

	cout << "Combien d'humain joueront ? : ";
	cin >> uiNbHumain;

	while (cin.fail() || uiNbHumain > uiNbJoueur || uiNbHumain == 0)
	{
		cout << "ERREUR : Nombre incoherent. Veuillez resaisir : ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> uiNbHumain;
	}

	cout << "\nIl y aura donc " << uiNbHumain << " humains et " << uiNbJoueur - uiNbHumain << " IA." << endl;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (uiBoucle = 0; uiBoucle < uiNbHumain; uiBoucle++)
	{
		string sNom = "";
		cout << "Veuillez ecrire le prenom du joueur N°"<< uiBoucle + 1 <<" : ";

		getline(cin, sNom);

		pjJeuALancer->JEU_AjouterJoueur(make_unique<CHumain>(sNom));
	}

	for (uiBoucle = uiNbHumain; uiBoucle < uiNbJoueur; uiBoucle++)
	{
		string sNom = "Joueur IA " + to_string(uiBoucle + 1 - uiNbHumain);;
		pjJeuALancer->JEU_AjouterJoueur(make_unique<Cia>(sNom));
	}

	cout << "\nVoici la liste des joueurs :" << endl;
	for (uiBoucle = 0; uiBoucle < uiNbJoueur; uiBoucle++)
	{
		cout << pjJeuALancer->JEU_GetNomJoueur(uiBoucle) << endl;
	}

	cout << "\n\nLe jeu demarre quand vous voulez." << endl;
	cout << "Veuillez presser ENTREE pour continuer.\n";

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	COS_LancerJeu(move(pjJeuALancer));
}

void CConsole::COS_LancerJeu(unique_ptr<CJeu> pjJeuALancer)
{
	COS_NettoyerEcran();

	cout << "----------------------------------------------------------" << endl;
	cout << "Debut du jeu : " << GRAS << pjJeuALancer->JEU_GetNom() << RESET << endl;
	cout << "----------------------------------------------------------\n" << endl;

	pjJeuALancer->JEU_JouerPartie();
}

void CConsole::COS_AttendreJoueurSuivant()
{
	COS_NettoyerEcran();

	cout << "----------------------------------------------------------" << endl;
	cout << "C'est au tour de :" << GRAS << "JEU_GetNomJoueur()" << RESET;
	cout << "----------------------------------------------------------\n" << endl;

	cout << "Veuillez passez l'ecran au prochain joueur.\n";
	cout << "Une fois fait, veuillez presser ENTREE pour continuer.\n";

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	COS_NettoyerEcran();
}