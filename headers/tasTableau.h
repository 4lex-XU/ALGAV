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
void reequilibrerTas (TasTableau * tas, int i);
Clef128 supprMin (TasTableau * tas);
void ajout (TasTableau * tas, Clef128 clef);
TasTableau * ajoutsIteratifs (Clef128* clefs[], int deb, int fin);
TasTableau * construction (Clef128* clefs[], int deb, int fin);
void affichageTasTableau(TasTableau* tas);
TasTableau * Union(TasTableau * tas1, TasTableau * tas2);
void delete(TasTableau * tas);
#endif