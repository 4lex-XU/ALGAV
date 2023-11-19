#include "clef128.h"
#ifndef H_TASTABLEAU
#define H_TASTABLEAU

typedef struct tasTableau TasTableau;
struct tasTableau {
    Clef128 * tab;
    int taille;
    int capacite;
};

TasTableau * initTas(int capacite);
void echanger (Clef128 * a, Clef128 * b);
void tasMin (TasTableau * tas, int i);
Clef128 supprMin (TasTableau * tas);
void ajout (TasTableau * tas, Clef128 clef);
TasTableau * ajoutIteratifs (Clef128 clefs[], int taille);
TasTableau * construction (Clef128 clefs[], int taille);

#endif