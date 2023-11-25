#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/clef128.h"
#include "../headers/tasArbre.h"
#include <time.h>
#include <math.h>

#define MAX 1000
#define NB_CLEF 200000

int main(int argc, char** argv){

    if(argc < 2)
    {
        printf("Error: file missing\n");
    }

    FILE* file = NULL;
    
    // OUVERTURE
    if((file = fopen(argv[1], "r")) == NULL)
    {
        printf("Error: not open\n");
    }

    Clef128* clefs[NB_CLEF];
    char buffer[MAX];
    int i = 0;

    // LECTURE DES CLES DANS LE FICHIER
    while(fgets(buffer, MAX, file) != NULL)
    {
        Clef128* clef = hexaToUnsigned(buffer);
        clefs[i] = clef;
        i++;
    }

    TasArbre* t1 = ajoutsIteratifs(clefs, 200000);
    printf("-------TAS ARBRE (AVANT)--------\n");
    affichageTasArbre(t1);

    Clef128 min = supprMin(t1, t1);
    printf("------CLEF MINIMUM------\n");
    affichageClef(&min);
    printf("-------TAS ARBRE (APRES)--------\n");
    affichageTasArbre(t1);

    return 0;
}