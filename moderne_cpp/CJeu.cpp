#include "CJeu.h"
#include "CJoueur.h"
#include "CRegle.h"
#include "CRegleDameDePique.h"
#include <iostream>

CJeu::CJeu() {
	// a faire
}

void CJeu::JEU_LancerPartie() {
	strategieRegle.REG_JouerPartie();
}

void CJeu::JEU_AjouterJoueur() {
	strategieJoueur.CJoueur();
}

