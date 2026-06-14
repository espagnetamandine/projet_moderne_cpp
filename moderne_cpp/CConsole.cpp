#include "CConsole.h"

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

	while (uiChoixJeu > vsCOS_listeJeu.size())
	{
		cout << "ERREUR : Choix invalide. Veuillez reselectionner votre choix : ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> uiChoixJeu;
	}
	if (uiChoixJeu > 0)
	{
		unique_ptr<CJeu> pjJeuALancer = make_unique<CJeu>(vsCOS_listeJeu[uiChoixJeu - 1]);
		COS_LancerJeu(move(pjJeuALancer));
		//COS_LancerJeu();
	}
}

void CConsole::COS_LancerJeu(unique_ptr<CJeu> pjJeuALancer)
{
	COS_NettoyerEcran();
	unsigned int uiNbJoueur, uiNbHumain;

	cout << "----------------------------------------------------------" << endl;
	cout << "Debut du jeu : " << GRAS << pjJeuALancer->JEU_GetNom() << RESET << endl;
	cout << "----------------------------------------------------------\n" << endl;

	cout << "A combien de joueurs souhaitez vous jouer ? : ";
	cin >> uiNbJoueur;

	while (!pjJeuALancer->JEU_SetNombreJoueur(uiNbJoueur))
	{
		cout << "ERREUR : Nombre de joueur impossible pour ce jeu. Veuillez resaisir : ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> uiNbJoueur;
	}

	cout << "\n\nVous etes " << uiNbJoueur << " a jouer !" << endl;

	cout << "Combien d'humain joueront ? : ";
	cin >> uiNbHumain;

	while (uiNbHumain > uiNbJoueur || uiNbHumain == 0)
	{
		cout << "ERREUR : Nombre incoherent. Veuillez resaisir : ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> uiNbHumain;
	}

	cout << "\n\nIl y aura donc " << uiNbHumain << " humains et " << uiNbJoueur - uiNbHumain << " IA." << endl;
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