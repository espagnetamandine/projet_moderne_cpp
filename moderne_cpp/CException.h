#ifndef CException_H
#define CException_H

class CException {
private:
    // ATTRIBUTS

    unsigned int uiEXT_CodeErreur;

public:
    // CONSTRUCTEURS ET DESTRUCTEUR

    /***********************************************************************
    * CException
    * **********************************************************************
    * Entrée : rien
    * Nécessite : rien
    * Sortie : rien
    * Entraîne : Initialiser uiEXT_CodeErreur au code par défaut 0
    * *********************************************************************/
    CException() { uiEXT_CodeErreur = 0; }

    // METHODES

    /***********************************************************************
    * EXT_ModifierCodeErreur | inline
    * **********************************************************************
    * Entrée : unsigned int uiCodeErreur
    * Nécessite : rien
    * Sortie : rien
    * Entraîne : Modifie la valeur de uiEXT_CodeErreur en uiCodeErreur
    * *********************************************************************/
    void setEXT_ModifierCodeErreur(unsigned int uiCodeErreur) { uiEXT_CodeErreur = uiCodeErreur; };

    /***********************************************************************
    * EXT_ModifierCodeErreur | inline
    * **********************************************************************
    * Entrée : EXT_LireCodeErreur
    * Nécessite : rien
    * Sortie : Retourne la valeur de uiEXT_CodeErreur
    * Entraîne : rien
    * *********************************************************************/
    unsigned int getEXT_LireCodeErreur() const { return uiEXT_CodeErreur; };
};

#endif