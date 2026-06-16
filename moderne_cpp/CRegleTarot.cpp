#include "CRegleTarot.h"
#include "CPaquet.h"
#include "CJoueur.h"
#include "CCarte.h"
#include "CEquipe.h"
#include "CConsole.h"
#include "CHumain.h"


bool CRegleTarot::REG_SetNbJoueur(unsigned int uiNbJoueurs)
{
	if (uiNbJoueurs==3 || uiNbJoueurs==4 || uiNbJoueurs==5)
	{
		uiNbJoueurPossible = uiNbJoueurs;
		return true;
	}
	return false;
}

void CRegleTarot::REG_DebutPartie(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points) {} // appelle constituer équipe
bool  CRegleTarot::REG_ConditionFinPartie(map<unique_ptr<CEquipe>, int>& points){}

unsigned int CRegleTarot::REG_DebutManche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int& uiJEU_IdJoueurCourrant) 
{
	cout << "\n-------------------------------------------------" << endl;
	cout << "               Debut de la manche                 " << endl;
	cout << "--------------------------------------------------" << endl;
	
	paquet->PAQ_Melanger();
	REG_MettreEnPlacePioche(paquet, joueurs);
	REG_DistribuerCartes(joueurs, paquet);
	
	unsigned int uiAnnonceMax = 0;
	unsigned int uiIndicePreneur = 0;
	
	for (unsigned int uiBoucle = 0; uiBoucle < joueurs.size(); uiBoucle++) {
		if (dynamic_cast<CHumain*>(joueurs[uiBoucle].get()) != nullptr)
		{
			cin.ignore();
			cin.get();
			REG_AfficherMainJoueur(joueurs[uiBoucle]);
		}
		cout << "\n " << joueurs[uiBoucle]->JOU_GetNomJoueur() << endl;
		cout << "\n Choississez parmi les options suivantes: Passer, Petite, Garde, Garde Sans, Garde Contre :" << endl;
		unsigned int uiChoix;
		cin >> uiChoix;
		while (uiChoix > 4 || (uiChoix>0 && uiChoix <= uiAnnonceMax)) {
			cout << "\n Choix invalide, recommencez " << endl;
			cin >> uiChoix;
		}
		if (uiChoix > uiAnnonceMax)
		{
			uiAnnonceMax = uiChoix;
			uiIndicePreneur = uiBoucle;
		}
		switch (uiChoix) 
		{
		case 0:
			cout << "\n Le joueur " << joueurs[uiBoucle]->JOU_GetNomJoueur() << " passe" << endl;
			break;
		case 1:
			cout << "\n Le joueur " << joueurs[uiBoucle]->JOU_GetNomJoueur() << " choisit Petite" << endl;
			break;
		case 2:
			cout << "\n Le joueur " << joueurs[uiBoucle]->JOU_GetNomJoueur() << " choisit Garde" << endl;
			break; 
		case 3:
			cout << "\n Le joueur " << joueurs[uiBoucle]->JOU_GetNomJoueur() << " choisit Garde Sans" << endl;
			break;
		case 4:
			cout << "\n Le joueur " << joueurs[uiBoucle]->JOU_GetNomJoueur() << " choisit Garde Contre" << endl;
			break;

		}

	

	}
	
	if (uiAnnonceMax == 0)
	{
		return REG_DebutManche(paquet, joueurs, points, uiJEU_IdJoueurCourrant);
	}
	else {
		REG_ChoixCarteChien(joueurs, uiIndicePreneur, uiAnnonceMax);
		return uiIndicePreneur;
	}
	

} 
bool  CRegleTarot::REG_ConditionFinManche(vector<unique_ptr<CJoueur>>& joueurs)
{
	if (joueurs[0]->JOU_GetMain()->PAQ_GetCartes().size() == 0)
	{
		return true;
	}
	return false;
}


void CRegleTarot::REG_ChoixCarteChien(vector<unique_ptr<CJoueur>>& joueurs, unsigned uiIndicePreneur, unsigned uiAnnonceMax)
{
	switch(uiAnnonceMax)
	{
	case 1:
	case 2:
		while (!pREG_Chien-> PAQ_GetCartes().empty())
		{
			unique_ptr<CCarte> carte = pREG_Chien->PAQ_RetirerCarte();
			joueurs[uiIndicePreneur]->JOU_GetMain()->PAQ_AjouterCarte(move(carte));
		}
		REG_AfficherMainJoueur(joueurs[uiIndicePreneur]);
		cout << "\n Faites votre jeux " << endl;
		unsigned int uiNbCartesChien = 0;
		if (joueurs.size() == 5)
		{
			uiNbCartesChien = 3;
		}
		else
		{
			uiNbCartesChien = 6;
		}
		for (unsigned int uiBoucle = 0; uiBoucle < uiNbCartesChien; uiBoucle++) {
			REG_AfficherMainJoueur(joueurs[uiIndicePreneur]);
			unsigned int uiIndiceCarte;
			cout << "\n Choississez les cartes que vous voulez mettre dans le chien" << endl;
			cin >> uiIndiceCarte;
			while (uiIndiceCarte > joueurs[uiIndicePreneur]->JOU_GetMain()->PAQ_GetCartes().size()-1)
			{
				cout << "\n Choix de carte invalide, recommencez " << endl;
				cin >> uiIndiceCarte;
			}
			unique_ptr<CCarte> carte = joueurs[uiIndicePreneur]->JOU_GetMain()->PAQ_RetirerCarte(uiIndiceCarte);
			pREG_Chien->PAQ_AjouterCarte(move(carte));
		}
		break;
		

	case 3:
		break;
	case 4 :
		break;
	}
	
}

void CRegleTarot::REG_ConstituerEquipes(vector<unique_ptr<CJoueur>>& joueurs, map<unique_ptr<CEquipe>, int>& points, unsigned int uiIndincePreneur)
{
	unique_ptr<CEquipe> pEquipePreneur = make_unique<CEquipe>();
	unique_ptr<CEquipe> pEquipeDefenseurs = make_unique<CEquipe>();
	pEquipePreneur->EQU_ajouterJoueur(uiIndincePreneur);
	if (joueurs.size() == 5)
	{
		unsigned int uiNbRois = 0;
		for (auto& carte : joueurs[uiIndincePreneur]-> JOU_GetMain()->PAQ_GetCartes())
		{
			
			if (carte->CAR_GetNom()== "Roi")
			{
				uiNbRois++;
			}
		}
		if (uiNbRois ==4)
		{
			for (unsigned int uiBoucle= 0; uiBoucle < joueurs.size(); uiBoucle++)
			{
				if (uiBoucle != uiIndincePreneur)
				{
					pEquipeDefenseurs->EQU_ajouterJoueur(uiBoucle);
				}
			}
		}
		else {
			
			cout << "\n Le joueur " << joueurs[uiIndincePreneur]->JOU_GetNomJoueur() << "appelle le Roi de " << endl;
			string sCouleurChoisie;
			cin >> sCouleurChoisie;
			while (sCouleurChoisie != "Coeur" && sCouleurChoisie != "Trefle" && sCouleurChoisie != "Carreau" && sCouleurChoisie != "Pique")
			{
				cout << "\n Couleur invalide, recommencez" << endl;
				cin >> sCouleurChoisie;
			}
			for (unsigned int uiBoucle = 0; uiBoucle < joueurs.size(); uiBoucle++)
			{
				if (uiBoucle != uiIndincePreneur)
				{
					bool bPossedeLeRoi = false ;
					for (auto& carte : joueurs[uiBoucle]->JOU_GetMain()->PAQ_GetCartes())
					{
						if (carte->CAR_GetNom() == "Roi" && carte->CAR_GetCouleur()== sCouleurChoisie)
						{
							bPossedeLeRoi = true;
						}
						
					}
					if (bPossedeLeRoi == true) {
						pEquipePreneur->EQU_ajouterJoueur(uiBoucle);
					}
					else {
						pEquipeDefenseurs->EQU_ajouterJoueur(uiBoucle);
					}
				}
			}

		}
		

	}
	else
	{
		for (unsigned int uiBoucle = 0; uiBoucle < joueurs.size(); uiBoucle++)
		{
			if (uiBoucle != uiIndincePreneur) {
				pEquipeDefenseurs->EQU_ajouterJoueur(uiBoucle);
			}
		}
	}
	points[move(pEquipePreneur)] = 0;
	points[move(pEquipeDefenseurs)] = 0;
}

void CRegleTarot::REG_MettreEnPlacePioche(unique_ptr<CPaquet>& paquet, vector<unique_ptr<CJoueur>>& joueurs)
{
	pREG_Chien = CPaquetManager::PAQ_CreerPaquet("Joueur");
	unsigned int uiNbCartesChien = 0;
	if (joueurs.size() == 5)
	{
		uiNbCartesChien = 3;
	}
	else
	{
		uiNbCartesChien = 6;
	}
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbCartesChien; uiBoucle++)
	{
		unique_ptr<CCarte> carte = paquet->PAQ_RetirerCarte();
		pREG_Chien->PAQ_AjouterCarte(move(carte));
	}

}





void CRegleTarot:: REG_DistribuerCartes(vector<unique_ptr<CJoueur>>& joueurs, unique_ptr<CPaquet>& paquet) 
{
	
	
	for (unsigned int uiBoucle = 0; uiBoucle < (((paquet->PAQ_GetCartes().size()) / joueurs.size())/3); uiBoucle++) //pas la methode dans CPaquet 
	{
		for (auto& joueur: joueurs) //CJoueur virtuelle pure
		{
			for (unsigned int uiBoucle2 = 0; uiBoucle2 < 3; uiBoucle2++)
			{
				unique_ptr<CCarte> carte = paquet->PAQ_RetirerCarte();
				joueur->JOU_GetMain()->PAQ_AjouterCarte(move(carte));
			}
			
		}
	}
}


bool CRegleTarot::REG_PremiereCarte(CCarte& carte) {
	return true;
}

bool CRegleTarot::REG_CarteValide(CCarte& carte, unique_ptr<CPaquet>& pPaquetJoueur)  // 
{
	return true;
}

unsigned int CRegleTarot::REG_DeterminerIndiceGagnantPli(unique_ptr<CPaquet>& pPli, vector<unsigned int>& vuIdJoueurPli) 
{
	pPli->PAQ_GetCartes()[0];
	unsigned int uiValeurAtoutMax = 0;
	unsigned int uiValeurCarteMax = 0;
	unsigned int uiIndiceGagnant = 0;
	for (unsigned int uiBoucle = 0; uiBoucle < vuIdJoueurPli.size(); uiBoucle++) 

	{
		
		if (pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetCouleur() == "Atout" && pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() != "L'excuse" && pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur()> uiValeurAtoutMax)
		{
			uiValeurAtoutMax = (pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur());
			uiIndiceGagnant = vuIdJoueurPli[uiBoucle];

		}
		else if (pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetCouleur() == pPli->PAQ_GetCartes()[0]->CAR_GetCouleur() && pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() != "L'excuse" && pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur() > uiValeurCarteMax)
		{
			uiValeurCarteMax = (pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur());
			uiIndiceGagnant = vuIdJoueurPli[uiBoucle];
		}
	}
	return uiIndiceGagnant;

}
void CRegleTarot::REG_CalculerPointsPli(unique_ptr<CPaquet>& pPli, map<unique_ptr<CEquipe>,int>& points, unsigned int uiIndiceGagnant, vector<unsigned int>& vuIdJoueurPli)
{
	int* iPointsEquipeGagnante = nullptr;

	for (auto& equipe: mREG_PointsManche)
	{
		equipe.first;
		equipe.second;
		if (find(equipe.first->getEQU_equipe().begin(), equipe.first->getEQU_equipe().end(), uiIndiceGagnant) != equipe.first->getEQU_equipe().end())
		{
			iPointsEquipeGagnante = &equipe.second;
		}
	}
	
	for (unsigned int uiBoucle = 0; uiBoucle < pPli->PAQ_GetCartes().size(); uiBoucle++)
	{
		if (pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() == "Roi" ||  (pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetCouleur() == "Atout" && (pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur() == 1 || pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur() == 21)))
		{
			*iPointsEquipeGagnante += 9;
		}
		else if (pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() == "L'excuse")
		{
			unsigned int uiIndiceJoueurExcuse = vuIdJoueurPli[uiBoucle];
			for (auto& equipeExcuse : mREG_PointsManche)
			{
				if(find(equipeExcuse.first->getEQU_equipe().begin(), equipeExcuse.first->getEQU_equipe().end(), uiIndiceJoueurExcuse) != equipeExcuse.first->getEQU_equipe().end())
				{
					equipeExcuse.second += 8;
				}
			}
			*iPointsEquipeGagnante += 1;
			

		}
		else if (pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() == "Dame")
		{
			*iPointsEquipeGagnante += 7;
		}
		else if (pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() == "Cavalier")
		{
			*iPointsEquipeGagnante += 5;
		}
		else if (pPli->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() == "Valet")
		{
			*iPointsEquipeGagnante += 3;
		}
		else 
		{
			*iPointsEquipeGagnante += 1;
		}
	}
}
void CRegleTarot::REG_CalculerPointsManche(map<unique_ptr<CEquipe>, int>& points, unsigned int uiIndicePreneur, unsigned int uiAnnonceMax, unique_ptr<CPaquet>& pDernierPli, unsigned int uiIndiceGagnantDernierPli, unique_ptr<CPaquet>& pCartesPreneur, vector<unique_ptr<CJoueur>>& joueurs) 
{
	unsigned int uiNbBouts=0;
	for (unsigned int uiBoucle=0; uiBoucle<pREG_Chien->PAQ_GetCartes().size(); uiBoucle++)
	{
		if (pREG_Chien->PAQ_GetCartes()[uiBoucle]->CAR_GetCouleur() == "Atout" && (pREG_Chien->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur() == 1 || pREG_Chien->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur() == 21 || pREG_Chien->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() == "L'excuse"))
		{
			uiNbBouts++;
		}
	}
	for (unsigned int uiBoucle = 0; uiBoucle < pCartesPreneur->PAQ_GetCartes().size(); uiBoucle++)
	{
		if (pCartesPreneur->PAQ_GetCartes()[uiBoucle]->CAR_GetCouleur() == "Atout" && (pCartesPreneur->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur() == 1 || pCartesPreneur->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur() == 21 || pCartesPreneur->PAQ_GetCartes()[uiBoucle]->CAR_GetNom() == "L'excuse"))
		{
			uiNbBouts++;
		}
	}
	unsigned int uiSeuilVictoire;
	switch (uiNbBouts)
	{
	case 0:
		uiSeuilVictoire = 56;
		break;
	case 1:
		uiSeuilVictoire = 51;
		break;
	case 2:
		uiSeuilVictoire = 41;
		break;
	case 3:
		uiSeuilVictoire = 36;
		break;
	}
	for (unsigned int uiBoucle = 0; uiBoucle < pDernierPli->PAQ_GetCartes().size(); uiBoucle++)
	{
		if (pDernierPli->PAQ_GetCartes()[uiBoucle]->CAR_GetCouleur() == "Atout" && pDernierPli->PAQ_GetCartes()[uiBoucle]->CAR_GetValeur() == 1)
		{
			for (auto& equipe : mREG_PointsManche)
			if (find(equipe.first->getEQU_equipe().begin(), equipe.first->getEQU_equipe().end(), uiIndicePreneur) != equipe.first->getEQU_equipe().end())
			{
				if (find(equipe.first->getEQU_equipe().begin(), equipe.first->getEQU_equipe().end(), uiIndiceGagnantDernierPli) != equipe.first->getEQU_equipe().end())
				{
					equipe.second += 10;
				}
				else 
				{
					equipe.second -= 10;
				}
			}
		}
	}
	int iPointsPreneur = 0;
	for (auto& equipe : mREG_PointsManche){
	
		if(find(equipe.first->getEQU_equipe().begin(), equipe.first->getEQU_equipe().end(), uiIndicePreneur) != equipe.first->getEQU_equipe().end())
		{
			iPointsPreneur = equipe.second;
		}
	}
	unsigned int uiMultiplicateur;
	switch (uiAnnonceMax)
	{
	case 1:
		uiMultiplicateur = 1;
		break;
	case 2:
		uiMultiplicateur = 2;
		break;
	case 3:
		uiMultiplicateur = 4;
		break;
	case 4:
		uiMultiplicateur = 6;
		break;
	}
	for (auto& equipe : points) {
		if(find(equipe.first->getEQU_equipe().begin(), equipe.first->getEQU_equipe().end(), uiIndicePreneur) != equipe.first->getEQU_equipe().end())
		{
			if (iPointsPreneur >= uiSeuilVictoire * 2)
			{
				equipe.second += (iPointsPreneur - uiSeuilVictoire * 2 + 25 * 2) * uiMultiplicateur * (joueurs.size()-1) ;
			}
			else
			{
				equipe.second -= (iPointsPreneur - uiSeuilVictoire * 2 + 25 * 2) * uiMultiplicateur * (joueurs.size() - 1);
			}
		}
		else
		{
			if (iPointsPreneur >= uiSeuilVictoire * 2)
			{
				equipe.second -= (iPointsPreneur - uiSeuilVictoire * 2 + 25 * 2) * uiMultiplicateur;
			}
			else
			{
				equipe.second += (iPointsPreneur - uiSeuilVictoire * 2 + 25 * 2) * uiMultiplicateur;
			}
		}
		
	}
}


void CRegleTarot::REG_AfficherGagnantPli(vector<unique_ptr<CJoueur>>&vJoueurs, unsigned int uiIndiceJoueurGagnantPli)
{
	cout << "\n Le joueur" << vJoueurs[uiIndiceJoueurGagnantPli]->JOU_GetNomJoueur() << " remporte le pli !" << endl;
}

void CRegleTarot::REG_AfficherGagnantManche(vector<unique_ptr<CJoueur>>& vJoueurs)
{
	int iPointsMax = 0;
	CEquipe* pEquipeGagnante = nullptr;
	for (auto& equipe : mREG_PointsManche) {

		if (equipe.second > iPointsMax)
		{
			iPointsMax = equipe.second;
			pEquipeGagnante = equipe.first.get();
		}
	}
	cout << "\n Les joueurs qui remportent la manche sont: " << endl;
	for (unsigned int uiBoucle : pEquipeGagnante->getEQU_equipe())
	{
		cout << vJoueurs[uiBoucle]->JOU_GetNomJoueur() << endl;
	}
}

void CRegleTarot::REG_AfficherGagnantPartie(vector<unique_ptr<CJoueur>>&vJoueurs, unsigned int uiIndiceJoueurGagnantPartie)
{
	cout << "\n Le joueur" << vJoueurs[uiIndiceJoueurGagnantPartie]->JOU_GetNomJoueur() << " remporte la partie !" << endl;
}

void CRegleTarot::REG_AfficherMainJoueur(unique_ptr<CJoueur>& pJoueur) 
{
	for (unsigned int uiBoucle = 0; uiBoucle < pJoueur->JOU_GetMain().size(); uiBoucle++)
	{
		cout << "carte " << uiBoucle << " : " << pJoueur[uiBoucle] << endl;
	}

} // appelle afficherpli
void CRegleTarot::REG_AfficherPoints(map<unique_ptr<CEquipe>, int>&mJEU_points)
{
}