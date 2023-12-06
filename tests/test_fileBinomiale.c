#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/clef128.h"
#include "../headers/fileBinomiale.h"
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
    FileBinomiale* F1 = Construction(clefs, 0, 1000);
    printf("-------CONSTRUCTION--------\n");
    affichageFileBinomiale(F1);

    FileBinomiale * F1A = SupprMin(F1);
    
    printf("-------FILE BINOMIALE (APRES)--------\n");
    affichageFileBinomiale(F1A);

    printf("\n");
    FileBinomiale* F2 = Construction(clefs, 0, 1000);
    printf("-------CONSTRUCTION--------\n");
    printf("-------FILE BINOMIALE (AVANT)--------\n");
    affichageFileBinomiale(F2);

    FileBinomiale * F2A = SupprMin(F2);

    printf("-------FILE BINOMIALE (APRES)--------\n");
    affichageFileBinomiale(F2A);

    printf("\n");
    
    FileBinomiale* F3 = Union(F1A, F2A);
    printf("-------UNION--------\n");
    printf("-------FILE BINOMIALE UNION F1 F2--------\n");
    affichageFileBinomiale(F3);

    // FERMETURE
    fclose(file);
    deleteClefs(clefs, NB_CLEF);
    deleteFileBinomiale(F1);
    deleteFileBinomiale(F2);
    deleteFileBinomiale(F3);

    return 0;
}