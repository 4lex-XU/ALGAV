#include "clef128.h"
#ifndef H_TASARBRE
#define H_TASARBRE

typedef struct tasArbre TasArbre;
struct tasArbre {
    Clef128 clef;
    struct tasArbre * fg;
    struct tasArbre * fd;
};

void SupprMin (TasArbre * tas);
void Ajout (TasArbre * tas, Clef128 clef);
void AjoutsIteratifs (TasArbre * tas, Clef128 clefs[]);

#endif