#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/clef128.h"
#include "../headers/tasArbre.h"
#include <time.h>
#include <math.h>

#define MAX 1000
#define NB_CLEF 1000

int main(int argc, char** argv){

    if(argc < 2)
    {
        printf("Error: file missing\n");
    }

    FILE* file = NULL;
    FILE* file2 = NULL;
    
    // OUVERTURE
    if((file = fopen(argv[1], "r")) == NULL)
    {
        printf("Error: not open\n");
    }

    if((file2 = fopen(argv[2], "r")) == NULL)
    {
        printf("Error: not open\n");
    }

    Clef128* clefs[NB_CLEF];
    Clef128* clefs2[NB_CLEF];
    char buffer[MAX];
    int i = 0, j = 0;

    // LECTURE DES CLES DANS LE FICHIER 1
    while(fgets(buffer, MAX, file) != NULL)
    {
        Clef128* clef = hexaToUnsigned(buffer);
        clefs[i] = clef;
        i++;
    }

    // LECTURE DES CLES DANS LE FICHIER 2
    while(fgets(buffer, MAX, file2) != NULL)
    {
        Clef128* clef = hexaToUnsigned(buffer);
        clefs2[j] = clef;
        j++;
    }
    
    // AJOUTS ITERATIFS
    TasArbre* t1 = ajoutsIteratifsTasArbre(clefs, 21);
    printf("-------AJOUTS ITERATIFS--------\n");
    affichageTasArbre(t1);
    
    // SUPPRESSION
    Clef128 min = supprMinTasArbre(t1, t1);
    printf("\n");   
    printf("------CLEF MINIMUM------\n");
    affichageClef(&min);
    printf("\n");
    printf("-------SUPPRESSION--------\n");
    affichageTasArbre(t1);
    
    // CONSTRUCTION
    TasArbre* t2 = constructionTasArbre(clefs, 15);
    printf("\n");
    printf("-------CONSTRUCTION--------\n");
    affichageTasArbre(t2);
    
    // UNION
    TasArbre* tas1 = constructionTasArbre(clefs, 5);
    TasArbre* tas2 = constructionTasArbre(clefs2, 5);
    printf("\n");
    printf("-------T1--------\n");
    affichageTasArbre(tas1);
    printf("\n");
    printf("-------T2--------\n");
    affichageTasArbre(tas2);
    TasArbre* tasUnion = UnionTasArbre(tas1, tas2);
    printf("\n");
    printf("-------UNION--------\n");
    affichageTasArbre(tasUnion);
    
    fclose(file);
    fclose(file2);

    deleteTasArbre(t1);
    deleteTasArbre(t2);
    deleteTasArbre(tas1);
    deleteTasArbre(tas2);
    deleteTasArbre(tasUnion);
    deleteClefs(clefs, NB_CLEF);
    deleteClefs(clefs2, NB_CLEF);

    return 0;
}