#ifndef _CCONSOLE_H
#define _CCONSOLE_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>

using namespace std;

class CJeu;
class CHumain;
class Cia;
class CEquipe;
class CPaquet;

class CConsole {
private:
	static vector<string> vsCOS_listeJeu;

	// Code ANSI statiques et constants
	static const string RESET;
	static const string ROUGE;
	static const string VERT;
	static const string JAUNE;
	static const string BLEU;
	static const string MAGENTA;
	static const string CYAN;
	static const string GRAS;

	static const string BG_BLANC;
	static const string BG_NOIR;

public:
	static void COS_ChoisirJeu();
	static void COS_PreparerJeu(unique_ptr<CJeu> pjJeuALancer);
	static void COS_LancerJeu(unique_ptr<CJeu> pjJeuALancer);
	static void COS_NettoyerEcran() { cout << "\033[2J\033[1;1H" << flush; }
	static void COS_AttendreJoueurSuivant();

	static void COS_AfficherEcranSecretJoueur(
		const string& sNomJoueur,
		const unique_ptr<CPaquet>& pMain,
		unsigned int uiNumeroEquipe,
		int iScoreEquipe
	);
};

#endif