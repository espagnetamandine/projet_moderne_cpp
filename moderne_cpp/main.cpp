#include <iostream>
#include <memory>

#include "CPaquetManager.h"
#include "CJoueur.h"
#include "CHumain.h"
#include "CEquipe.h"
#include "Cia.h"
#include "CConsole.h"

using namespace std;

int main(int argc, char* argv[])
{
	CConsole::COS_ChoisirJeu();

	//unique_ptr<CPaquet> paquetTarot = CPaquetManager::PAQ_CreerPaquet("Tarot");

	//paquetTarot->PAQ_Afficher();
	//cout << "\n\n\n";
	//paquetTarot->PAQ_Melanger();
	//paquetTarot->PAQ_Afficher();

	//cout << "\n\n\n";

	//cout << "\033[031mDistribution pour Joueur 1 :\n" << endl;

	//unique_ptr<CPaquet> mainJoueur1 = CPaquetManager::PAQ_creerPaquer("Joueur"); // ou "Main du joueur"
	//mainJoueur1->PAQ_ajouterCarte(paquetTarot->PAQ_retirerCarte()); // -1 ou rien pour la dernière carte de la pioche
	//																// sinon vous pouvez préciser l'indice de la carte
	//mainJoueur1->PAQ_afficher();

	//cout << "\n\n\nResultat sur le paquet :";

	//paquetTarot->PAQ_afficher();

	//// Exemple avec l'indice :

	//cout << "\n\n\nAffichage des deux mains :";

	//unique_ptr<CPaquet> mainJoueur2 = CPaquetManager::PAQ_creerPaquer("Main du joueur");
	//mainJoueur1->PAQ_ajouterCarte(paquetTarot->PAQ_retirerCarte());
	//mainJoueur1->PAQ_ajouterCarte(paquetTarot->PAQ_retirerCarte());
	//mainJoueur2->PAQ_ajouterCarte(paquetTarot->PAQ_retirerCarte());
	//mainJoueur2->PAQ_ajouterCarte(paquetTarot->PAQ_retirerCarte());
	//mainJoueur2->PAQ_ajouterCarte(paquetTarot->PAQ_retirerCarte());

	//mainJoueur1->PAQ_afficher();
	//mainJoueur2->PAQ_afficher();

	//// changement de main (le joueur 1 récupère une carte du joueur 2

	//cout << "\n\n\nAffichage des deux mains :";

	//// pour la main du joueur
	//mainJoueur1->PAQ_ajouterCarte(mainJoueur2->PAQ_retirerCarte(2));

	//mainJoueur1->PAQ_afficher();
	//mainJoueur2->PAQ_afficher();

	//CHumain Joueur1;
	//Cia Joueur2;
	//Cia Joueur3;
	//Cia Joueur4;
	//Joueur1.JOUEUR_SetsNomJoueur("Yann");
	//Joueur2.JOUEUR_SetsNomJoueur("IA_1");
	//Joueur3.JOUEUR_SetsNomJoueur("IA_2");
	//Joueur4.JOUEUR_SetsNomJoueur("IA_3");

	//CEquipe Equipe_1;
	//CEquipe Equipe_2;

	//Equipe_1.EQU_AjouterJoueur(&Joueur1);
	//Equipe_1.EQU_AjouterJoueur(&Joueur2);
	//Equipe_2.EQU_AjouterJoueur(&Joueur3);
	//Equipe_2.EQU_AjouterJoueur(&Joueur4);

	//Equipe_1.EQU_SetuiNumeroEquipe(1);
	//Equipe_2.EQU_SetuiNumeroEquipe(2);



	return EXIT_SUCCESS;
}