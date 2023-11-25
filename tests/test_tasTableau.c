#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/clef128.h"
#include "../headers/tasTableau.h"
#include <time.h>
#include <math.h>

#define MAX 1000
#define NB_CLEF 200000

int main(int argc, char** argv){

    if(argc < 2)
    {
        printf("Error: file missing\n");
        return 0;
    }

    FILE* file = NULL;
    
    // OUVERTURE
    if((file = fopen(argv[1], "r")) == NULL)
    {
        printf("Error: not open\n");
        return 0;
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

    TasTableau* t1 = ajoutsIteratifs(clefs, 200000);
    printf("-------AJOUT ITERATIF--------\n");
    printf("-------TAS Tableau (AVANT)--------\n");
    affichageTasTableau(t1);

    Clef128 min = supprMin(t1);
    printf("------CLEF MINIMUM------\n");
    affichageClef(&min);
    printf("-------TAS TABLEAU (APRES)--------\n");
    affichageTasTableau(t1);

    printf("\n");

    /*TasTableau* t2 = construction(clefs, 200000);
    printf("-------CONSTRUCTION--------\n");
    printf("-------TAS Tableau (AVANT)--------\n");
    affichageTasTableau(t2);

    min = supprMin(t2);
    printf("------CLEF MINIMUM------\n");
    affichageClef(&min);
    printf("-------TAS TABLEAU (APRES)--------\n");
    affichageTasTableau(t2);*/

    return 0;
}