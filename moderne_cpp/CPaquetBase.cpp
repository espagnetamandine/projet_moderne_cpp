#include "CPaquetBase.h"

/********************************************************/
/*                       METHODES                       */
/********************************************************/

void CPaquetBase::PAQ_Afficher() const
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
		cout << *(vcPAQ_paquet[uiBoucleVector]) << endl;
	}
};

void CPaquetBase::PAQ_AfficherSansCouleurs() const
{
	unsigned int uiBoucleVector;

	cout << "\nCartes du paquet (" << vcPAQ_paquet.size() << " cartes) : " << endl;

	for (uiBoucleVector = 0; uiBoucleVector < vcPAQ_paquet.size(); uiBoucleVector++)
	{
		cout << *(vcPAQ_paquet[uiBoucleVector]) << endl;
	}
}

void CPaquetBase::PAQ_AfficherAvecIdentifiant() const
{
	unsigned int uiBoucleVector;

	cout << "\nCartes du paquet (" << vcPAQ_paquet.size() << " cartes) : " << endl;

	for (uiBoucleVector = 0; uiBoucleVector < vcPAQ_paquet.size(); uiBoucleVector++)
	{
		cout << "Carte " << uiBoucleVector + 1 << " : " << * (vcPAQ_paquet[uiBoucleVector]) << endl;
	}
};

void CPaquetBase::PAQ_Melanger()
{
	random_device graineMelange;
	mt19937 algoMelange(graineMelange());

	shuffle(vcPAQ_paquet.begin(), vcPAQ_paquet.end(), algoMelange);
}

unique_ptr<CCarte> CPaquetBase::PAQ_RetirerCarte(int iIndiceCarte)
{
	if (iIndiceCarte == -1)
	{
		iIndiceCarte = vcPAQ_paquet.size() - 1;
	}
	if (iIndiceCarte >= (int)vcPAQ_paquet.size())
	{
		throw out_of_range("Indice trop grand. Supérieur au nombre de carte.");
	}
	if (vcPAQ_paquet.empty())
	{
		throw out_of_range("Paquet vide.");
	}


	unique_ptr<CCarte> pCarteARetirer = move(vcPAQ_paquet[iIndiceCarte]);

	vcPAQ_paquet.erase(vcPAQ_paquet.begin() + iIndiceCarte);

	return pCarteARetirer;
}

void CPaquetBase::PAQ_AjouterCarte(unique_ptr<CCarte> pCarteAAjouter)
{
	if (pCarteAAjouter != nullptr)
	{
		vcPAQ_paquet.push_back(move(pCarteAAjouter));
	}
}
