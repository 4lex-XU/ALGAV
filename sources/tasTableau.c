#include <stdio.h>
#include <stdlib.h>
#include "../headers/tasTableau.h"

void initTas(TasTableau* tas, int taille) 
{
    tas->taille = 0;
    tas->tab = (Clef128*)malloc(sizeof(Clef128)*taille);
}

void SupprMin (TasTableau * tas) 
{
    if (tas->taille == 0) {
        printf("Tas vide\n");
        return;
    }
    tas->tab[0] = tas->tab[tas->taille-1]; // On remplace le min par le dernier élément
    tas->taille--;  
    int i = 0; // Pere
    // On fait descendre le min à sa place
    while (2*i+1 < tas->taille) { // Tant qu'il a un fils
        int j = 2*i+1; // Fils gauche
        if (j+1 < tas->taille && !(inf(&tas->tab[j], &tas->tab[j+1]))) {  // On prend le plus petit des deux fils
            j++;
        }
        if (inf(&tas->tab[i], &tas->tab[j])) { // Si le fils est plus grand que le père on échange
            Clef128 tmp = tas->tab[i];
            tas->tab[i] = tas->tab[j];
            tas->tab[j] = tmp;
            i = j;
        } else { // Sinon on a fini
            break;
        }
    }
}

void Ajout (TasTableau * tas, Clef128 clef) {
    tas->tab[tas->taille++] = clef;
    int i = tas->taille;
    while (i > 0 && inf(&tas->tab[i/2-1], &tas->tab[i])) { // Tant que le père est plus petit que le fils
        Clef128 tmp = tas->tab[i];
        tas->tab[i] = tas->tab[i/2-1];
        tas->tab[i/2-1] = tmp;
        i = i/2-1;
    }
}

void AjoutIteratifs (TasTableau * tas, Clef128 clefs[], int taille) {
    for (int i = 0; i < taille; i++) {
        Ajout(tas, clefs[i]);
    }
}