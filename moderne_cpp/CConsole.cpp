#include "CConsole.h"
#include "CJeu.h"
#include "CHumain.h"
#include "CJoueur.h"
#include "Cia.h"
#include "CEquipe.h"
#include "CPaquet.h"

using namespace std;

/********************************************************/
/*                      ATTRIBUTS                       */
/********************************************************/

vector<string> CConsole::vsCOS_listeJeu = { "Dame de pique", "Tarot", "Belote" };

const string CConsole::RESET = "\033[0m";
const string CConsole::ROUGE = "\033[31m";
const string CConsole::VERT = "\033[32m";
const string CConsole::JAUNE = "\033[33m";
const string CConsole::BLEU = "\033[34m";
const string CConsole::MAGENTA = "\033[35m";
const string CConsole::CYAN = "\033[36m";
const string CConsole::GRAS = "\033[1m";

const string CConsole::BG_BLANC = "\033[47m";
const string CConsole::BG_NOIR = "\033[40m";

/********************************************************/
/*                       METHODES                       */
/********************************************************/

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
		CConsole::COS_PreparerJeu(move(pjJeuALancer));
	}
}

void CConsole::COS_PreparerJeu(unique_ptr<CJeu> pjJeuALancer)
{
	CConsole::COS_NettoyerEcran();
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

	cout << "\nVous etes " << uiNbJoueur << " a jouer !" << endl;

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
		cout << "Veuillez ecrire le prenom du joueur N°" << uiBoucle + 1 << " : ";

		getline(cin, sNom);

		pjJeuALancer->JEU_AjouterJoueur(make_unique<CHumain>(sNom));
	}

	for (uiBoucle = uiNbHumain; uiBoucle < uiNbJoueur; uiBoucle++)
	{
		string sNom = "Joueur IA " + to_string(uiBoucle + 1 - uiNbHumain);
		pjJeuALancer->JEU_AjouterJoueur(make_unique<Cia>(sNom));
	}

	cout << "\nVoici la liste des joueurs :" << endl;
	for (uiBoucle = 0; uiBoucle < uiNbJoueur; uiBoucle++)
	{
		cout << pjJeuALancer->JEU_GetNomJoueur(uiBoucle) << endl;
	}

	cout << "\nLe jeu demarre quand vous voulez." << endl;
	cout << "Veuillez presser ENTREE pour continuer.\n";

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	CConsole::COS_LancerJeu(move(pjJeuALancer));
}

void CConsole::COS_LancerJeu(unique_ptr<CJeu> pjJeuALancer)
{
	CConsole::COS_NettoyerEcran();

	cout << "--------------------------------------------------" << endl;
	cout << "          Debut du jeu : " << GRAS << pjJeuALancer->JEU_GetNom() << RESET << endl;
	cout << "--------------------------------------------------\n" << endl;

	pjJeuALancer->JEU_JouerPartie();
}

void CConsole::COS_AfficherGagnants(const vector<string>& vsPrenomsGagnants, const string& sNomEquipe) {
	CConsole::COS_NettoyerEcran();
	
	cout << JAUNE << GRAS << "--------------------------------------------------" << endl;
	cout << "               Fin de la partie                   " << endl;
	cout << "--------------------------------------------------\n" << RESET << endl;

	if (!sNomEquipe.empty()) {
		cout << VERT << GRAS << "Victoire de l'equipe : " << sNomEquipe << RESET << endl;
	}
	else {
		cout << VERT << GRAS << "Victoire individuelle !" << RESET << endl;
	}

	cout << "Felicitations a : ";
	for (size_t i = 0; i < vsPrenomsGagnants.size(); ++i) {
		cout << GRAS << vsPrenomsGagnants[i] << RESET;
		if (i < vsPrenomsGagnants.size() - 1) {
			cout << " & ";
		}
	}
	cout << " !" << endl;
	cout << JAUNE << GRAS << "\n--------------- Merci d'avoir joue ---------------\n" << RESET << endl;
}

void CConsole::COS_AttendreJoueurSuivant(string sNomJoueur)
{
	CConsole::COS_NettoyerEcran();

	cout << "--------------------------------------------------" << endl;
	cout << "          Joueur suivant :  " << GRAS << sNomJoueur << RESET << endl;
	cout << "--------------------------------------------------\n" << endl;

	cout << "Veuillez passer l'ecran au prochain joueur.\n";
	cout << "Une fois fait, veuillez presser ENTREE pour continuer.";

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	CConsole::COS_NettoyerEcran();
}

void CConsole::COS_AfficherEcranSecretJoueur(
	const unique_ptr<CJoueur>& pJoueur,
	unsigned int uiNumeroEquipe,
	int iScoreEquipe)
{
	CConsole::COS_AttendreJoueurSuivant(pJoueur->JOU_GetNomJoueur());

	cout << "--------------------------------------------------" << endl;
	cout << "              Joueur : " << GRAS << pJoueur->JOU_GetNomJoueur() << RESET << endl;

	if (uiNumeroEquipe != 0)
	{
		cout << BLEU << " Equipe : " << uiNumeroEquipe << "." << RESET;
	}
	if (uiNumeroEquipe != 0)
	{
		cout << BLEU << " Vous avez " << iScoreEquipe << " points." << RESET;
	}
	cout << "\n--------------------------------------------------\n" << endl;

	cout << "Voici votre main: " << endl;
	if (pJoueur->JOU_GetMain() != nullptr) {
		pJoueur->JOU_GetMain()->PAQ_AfficherAvecIdentifiant();
	}
}

