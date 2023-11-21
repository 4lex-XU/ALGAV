#include "clef128.h"
#ifndef H_TASARBRE
#define H_TASARBRE

typedef struct tasArbre TasArbre;
struct tasArbre {
    Clef128* clef;
    struct tasArbre * fg;
    struct tasArbre * fd;
    struct tasArbre * parent; // parent du noeud
    int hauteur; // hauteur de l'arbre
    int noeud; // nombre de noeud present dans l'arbre
};

Clef128 supprMin (TasArbre* tas, TasArbre* racine);
void ajout (TasArbre * tas, Clef128* clef);
TasArbre* ajoutsIteratifs (Clef128* clefs[], int len);
TasArbre* creerNoeud(Clef128* clef);
void echange(Clef128* a, Clef128* b);
void affichageTasArbre(TasArbre* tas);
void comparaison(TasArbre* t);
void majHauteurAjout(TasArbre* tas);
void majNoeudAjout(TasArbre* tas);
void majHauteurSuppr(TasArbre* tas);
void majNoeudSuppr(TasArbre* tas);
TasArbre* construction(Clef128* clefs[], int len);
TasArbre* Union(TasArbre* tas1, TasArbre* tas2);

#endif