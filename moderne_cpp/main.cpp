#include <iostream>
#include <memory>

#include "CPaquetBase.h"
#include "CPaquetDecorateurJeu32.h"
#include "CPaquetDecorateurJeu52.h"
#include "CPaquetDecorateurAjouterJoker.h"

using namespace std;

int main(int argc, char* argv[])
{
	unique_ptr<CPaquet> monPaquet = make_unique<CPaquetBase>();

	monPaquet = make_unique<CPaquetDecorateurJeu32>(move(monPaquet));
	monPaquet = make_unique<CPaquetDecorateurAjouterJoker>(move(monPaquet));

	monPaquet->PAQ_afficher();

	cout << "\n\n\n";

	monPaquet->PAQ_melanger();
	monPaquet->PAQ_afficher();


	return EXIT_SUCCESS;
}