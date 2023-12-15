#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../headers/arbreRecherche.h"
#include "../headers/clef128.h"

#define MAX 1000
#define NB_CLEF 1000

int main (int argc, char** argv) {
    Noeud* racine = NULL;
    Clef128* clef = hexaToUnsigned("0x00000000000000000000000000000000");
    racine = inserer(racine, clef);
    clef = hexaToUnsigned("0x00000000000000000000000000000001");
    racine = inserer(racine, clef);
    clef = hexaToUnsigned("0x00000000000000000000000000000002");
    racine = inserer(racine, clef);
    clef = hexaToUnsigned("0x00000000000000000000000000003");
    racine = inserer(racine, clef);

    printf("%d\n", rechercher(racine, hexaToUnsigned("0x00000000000000000000000000000000")));
    
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

    // LECTURE DES CLES DANS LE FICHIER 1
    while(fgets(buffer, MAX, file) != NULL)
    {
        Clef128* clef = hexaToUnsigned(buffer);
        clefs[i] = clef;
        i++;
    }

    Noeud* a1 = ajoutsIteratifsArbreRecherche(clefs, 10);
    printf("-------AJOUTS ITERATIFS--------\n");
    affichageArbre(a1);

    deleteClefs(clefs, NB_CLEF);
    deleteArbreRecherche(a1);

    return 0;
}