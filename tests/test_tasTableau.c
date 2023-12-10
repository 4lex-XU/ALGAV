#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/clef128.h"
#include "../headers/tasTableau.h"
#include <time.h>
#include <math.h>

#define MAX 1000
#define NB_CLEF 1000

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

    TasTableau* t1 = ajoutsIteratifsTasTableau(clefs, 0, 7);
    printf("-------AJOUT ITERATIF--------\n");
    printf("-------TAS Tableau (AVANT)--------\n");
    affichageTasTableau(t1);

    Clef128 min = supprMinTasTableau(t1);
    printf("------CLEF MINIMUM------\n");
    affichageClef(&min);
    printf("-------TAS TABLEAU (APRES)--------\n");
    affichageTasTableau(t1);

    printf("\n");

    TasTableau* t2 = constructionTasTableau(clefs, 7, 13);
    printf("-------CONSTRUCTION--------\n");
    printf("-------TAS Tableau (AVANT)--------\n");
    affichageTasTableau(t2);

    min = supprMinTasTableau(t2);
    printf("------CLEF MINIMUM------\n");
    affichageClef(&min);
    printf("-------TAS TABLEAU (APRES)--------\n");
    affichageTasTableau(t2);

    printf("\n");
    TasTableau* t3 = UnionTasTableau(t1, t2);
    printf("-------UNION--------\n");
    affichageTasTableau(t3);

    // FERMETURE
    fclose(file);
    deleteClefs(clefs, NB_CLEF);
    deleteTasTableau(t1);
    deleteTasTableau(t2);
    deleteTasTableau(t3);

    return 0;
}