#include <iostream>
#include <memory>

#include "CPaquetManager.h"

using namespace std;

int main(int argc, char* argv[])
{
	unique_ptr<CPaquet> paquetTarot = CPaquetManager::creerPaquet("Tarot");

	paquetTarot->PAQ_afficher();
	cout << "\n\n\n";
	paquetTarot->PAQ_melanger();
	paquetTarot->PAQ_afficher();

	// pour les mains MainJoueur.PAQ_ajouterCarte(move(monPaquet->PAQ_retirerCarte()))


	return EXIT_SUCCESS;
}