#include "clef128.h"
#ifndef H_TASARBRE
#define H_TASARBRE

typedef struct tasArbre TasArbre;
struct tasArbre {
    Clef128 clef;
    struct tasArbre * fg;
    struct tasArbre * fd;
};

TasArbre * creerNoeud (Clef128 clef);;
void echanger (Clef128 * a, Clef128 * b);
void reequilibrerTas (TasArbre * tas);
void supprMin (TasArbre * tas);
void ajout (TasArbre ** tas, Clef128 clef);
void ajoutsIteratifs (TasArbre * tas, Clef128 clefs[]);

#endif