#include "CRegleTarot.h"
#include "CJoueur.h"
#include "CPaquet.h"

void CRegleTarot::REG_DistribuerCartes(vector<CJoueur> joueurs, CPaquet paquet) {
	for (unsigned int i = 0; i < (paquet.getPAQ_cartes().size() / vjREG_joueurs.size()); i++) //pas la methode dans CPaquet 
	{
		for (CJoueur &joueur : vjREG_joueurs) //CJoueur virtuelle pure
		{
			joueur.JOUEUR_Choix_Carte_A_Jouer(pREG_paquet_de_cartes[i]);
		}
	}
}