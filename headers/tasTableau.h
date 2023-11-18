#include "clef128.h"
#ifndef H_TASTABLEAU
#define H_TASTABLEAU

typedef struct tasTableau TasTableau;
struct tasTableau {
    Clef128 * tab;
    int taille;
};

void initTas(TasTableau* tas, int taille);
void SupprMin (TasTableau * tas);
void Ajout (TasTableau * tas, Clef128 clef);
void AjoutsIteratifs (TasTableau * tas, Clef128 clefs[], int taille);

#endif