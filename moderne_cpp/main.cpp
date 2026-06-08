#include <iostream>
#include <memory>

#include "CPaquetManager.h"

using namespace std;

int main(int argc, char* argv[])
{
	unique_ptr<CPaquet> paquetTarot = CPaquetManager::PAQ_creerPaquer("Tarot");

	paquetTarot->PAQ_afficher();
	cout << "\n\n\n";
	paquetTarot->PAQ_melanger();
	paquetTarot->PAQ_afficher();

	cout << "\n\n\n";

	cout << "\033[031mDistribution pour Joueur 1 :\n" << endl;

	unique_ptr<CPaquet> mainJoueur1 = CPaquetManager::PAQ_creerPaquer("Joueur"); // ou "Main du joueur"
	mainJoueur1->PAQ_ajouterCarte(paquetTarot->PAQ_retirerCarte()); // -1 ou rien pour la dernière carte de la pioche
																	// sinon vous pouvez préciser l'indice de la carte
	mainJoueur1->PAQ_afficher();

	cout << "\n\n\nResultat sur le paquet :";

	paquetTarot->PAQ_afficher();

	// Exemple avec l'indice :

	cout << "\n\n\nAffichage des deux mains :";

	unique_ptr<CPaquet> mainJoueur2 = CPaquetManager::PAQ_creerPaquer("Main du joueur");
	mainJoueur1->PAQ_ajouterCarte(paquetTarot->PAQ_retirerCarte());
	mainJoueur1->PAQ_ajouterCarte(paquetTarot->PAQ_retirerCarte());
	mainJoueur2->PAQ_ajouterCarte(paquetTarot->PAQ_retirerCarte());
	mainJoueur2->PAQ_ajouterCarte(paquetTarot->PAQ_retirerCarte());
	mainJoueur2->PAQ_ajouterCarte(paquetTarot->PAQ_retirerCarte());

	mainJoueur1->PAQ_afficher();
	mainJoueur2->PAQ_afficher();

	// changement de main (le joueur 1 récupère une carte du joueur 2

	cout << "\n\n\nAffichage des deux mains :";

	// pour la main du joueur
	mainJoueur1->PAQ_ajouterCarte(mainJoueur2->PAQ_retirerCarte(2));

	mainJoueur1->PAQ_afficher();
	mainJoueur2->PAQ_afficher();


	return EXIT_SUCCESS;
}