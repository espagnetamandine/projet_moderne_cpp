#include <iostream>
#include <memory>

#include "CPaquetBase.h"
#include "CPaquetDecorateurJeu32.h"
#include "CPaquetDecorateurJeu52.h"
#include "CPaquetDecorateurAjouterJoker.h"
#include "CJoueur.h"
#include "CHumain.h"
#include "CEquipe.h"
#include "Cia.h"


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

	CHumain Joueur1;
	Cia Joueur2;
	Cia Joueur3;
	Cia Joueur4;
	Joueur1.JOUEUR_SetsNomJoueur("Yann");
	Joueur2.JOUEUR_SetsNomJoueur("IA_1");
	Joueur3.JOUEUR_SetsNomJoueur("IA_2");
	Joueur4.JOUEUR_SetsNomJoueur("IA_3");

	CEquipe Equipe_1;
	CEquipe Equipe_2;

	Equipe_1.EQU_AjouterJoueur(&Joueur1);
	Equipe_1.EQU_AjouterJoueur(&Joueur2);
	Equipe_2.EQU_AjouterJoueur(&Joueur3);
	Equipe_2.EQU_AjouterJoueur(&Joueur4);

	Equipe_1.EQU_SetuiNumeroEquipe(1);
	Equipe_2.EQU_SetuiNumeroEquipe(2);



	return EXIT_SUCCESS;
}