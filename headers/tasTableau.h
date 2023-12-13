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
Clef128 supprMinTasTableau (TasTableau * tas);
void ajoutTasTableau (TasTableau * tas, Clef128 clef);
TasTableau * ajoutsIteratifsTasTableau (Clef128* clefs[], int deb, int fin);
TasTableau * constructionTasTableau (Clef128* clefs[], int deb, int fin);
void affichageTasTableau(TasTableau* tas);
TasTableau * UnionTasTableau(TasTableau * tas1, TasTableau * tas2);
void deleteTasTableau(TasTableau * tas);
#endif