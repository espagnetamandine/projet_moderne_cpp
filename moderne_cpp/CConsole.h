#ifndef _CCONSOLE_H
#define _CCONSOLE_H

#include "CJeu.h"

#include <string>
#include <vector>
#include <iostream>
#include <memory>

using namespace std;

class CConsole {
private:
	vector<string> vsCOS_listeJeu;

	// Code ANSI
	const string RESET = "\033[0m";
	const string ROUGE = "\033[31m";
	const string VERT = "\033[32m";
	const string JAUNE = "\033[33m";
	const string BLEU = "\033[34m";
	const string MAGENTA = "\033[35m";
	const string CYAN = "\033[36m";
	const string GRAS = "\033[1m";

	const string BG_BLANC = "\033[47m";
	const string BG_NOIR = "\033[40m";

public:
	CConsole()
	{
		vsCOS_listeJeu.insert(vsCOS_listeJeu.end(), {
			"Dame de pique",
			"Tarot",
			"Belote",
		});
	};
	void COS_ChoisirJeu();
	// 
	void COS_LancerJeu(unique_ptr<CJeu> pjJeuALancer);

	void COS_NettoyerEcran() { cout << "\033[2J\033[1;1H" << flush; }
	void COS_AttendreJoueurSuivant();

};


#endif 