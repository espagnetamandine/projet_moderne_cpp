#include "CPaquetBase.h"

void CPaquetBase::PAQ_afficher() const
{
	unsigned int uiBoucleVector;

	cout << "Couleurs du paquet : " << endl;
	for (uiBoucleVector = 0; uiBoucleVector < vsPAQ_couleurs.size(); uiBoucleVector++)
	{
		cout << vsPAQ_couleurs[uiBoucleVector] << endl;
	}

	cout << "\nCartes du paquet (" << vcPAQ_paquet.size() << " cartes) : " << endl;

	for (uiBoucleVector = 0; uiBoucleVector < vcPAQ_paquet.size(); uiBoucleVector++)
	{
		cout << vcPAQ_paquet[uiBoucleVector] << endl;
	}
};

void CPaquetBase::PAQ_melanger()
{
	random_device graineMelange;
	mt19937 algoMelange(graineMelange());

	shuffle(vcPAQ_paquet.begin(), vcPAQ_paquet.end(), algoMelange);
}