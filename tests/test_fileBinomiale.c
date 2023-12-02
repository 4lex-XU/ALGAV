#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/clef128.h"
#include "../headers/fileBinomiale.h"
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

    FileBinomiale * F1 = construction(clefs, 0, 13);
    printf("-------CONSTRUCTION--------\n");
    printf("-------TAS Tableau (AVANT)--------\n");
    affichageFileBinomiale(F1);

    FileBinomiale * F1A = supprMin(F1);
    
    printf("-------TAS TABLEAU (APRES)--------\n");
    affichageFileBinomiale(F1A);

    printf("\n");
    FileBinomiale* F2 = construction(clefs, 14, 27);
    printf("-------CONSTRUCTION--------\n");
    printf("-------TAS Tableau (AVANT)--------\n");
    affichageFileBinomiale(F2);

    FileBinomiale * F2A = supprMin(F2);

    printf("-------TAS TABLEAU (APRES)--------\n");
    affichageFileBinomiale(F2A);

    printf("\n");
    
    FileBinomiale* F3 = Union(F1, F2);
    printf("-------UNION--------\n");
    printf("-------TAS Tableau (AVANT)--------\n");
    affichageFileBinomiale(F3);

    // FERMETURE
    fclose(file);
    deleteClefs(clefs, NB_CLEF);
    deleteFile(F1);
    deleteFile(F1A);
    deleteFile(F2);
    deleteFile(F2A);
    deleteFile(F3);

    return 0;
}