#include "clef128.h"
#ifndef H_TASARBRE
#define H_TASARBRE

typedef struct tasArbre TasArbre;
struct tasArbre {
    Clef128* clef;
    struct tasArbre * fg;
    struct tasArbre * fd;
    int hauteur; // hauteur de l'arbre
    int noeud; // nombre de noeud present dans l'arbre
};

Clef128 supprMin (TasArbre * tas);
void ajout (TasArbre * tas, Clef128* clef);
TasArbre* ajoutsIteratifs (Clef128* clefs[], int len);
TasArbre* creerNoeud(Clef128* clef);
void initialisation(TasArbre* t);
void echange(Clef128* a, Clef128* b);
void affichageTasArbre(TasArbre* tas);
void comparaison(TasArbre* t);

#endif