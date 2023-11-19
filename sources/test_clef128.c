#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/clef128.h"
#include <time.h>

#define MAX 1000
#define NB_CLEF 1000

int main(int argc, char** argv)
{
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

    // CLEFS ALEATOIRE
    srand(time(NULL));
    int k1, k2;
    do{
        k1 = rand()%NB_CLEF+1;
        k2 = rand()%NB_CLEF+1;
    }while(k1 == k2);

    printf("Clef 1 = %s -> %u %u %u %u\n", clefs[k1]->clef_hexa, clefs[k1]->b32_4, clefs[k1]->b32_3, clefs[k1]->b32_2, clefs[k1]->b32_1);
    printf("Clef 2 = %s -> %u %u %u %u\n", clefs[k2]->clef_hexa, clefs[k2]->b32_4, clefs[k2]->b32_3, clefs[k2]->b32_2, clefs[k2]->b32_1);

    // TEST FONCTIONS
    if(inf(clefs[k1], clefs[k2]) == 1)
    {
        printf("La clé : %s est strictement superieur à la clé : %s\n",
        clefs[k2]->clef_hexa, clefs[k1]->clef_hexa);
    }
    else{
        printf("La clé : %s\n est superieur ou egal à la clé : %s\n",
        clefs[k1]->clef_hexa, clefs[k2]->clef_hexa);
    }

    if(eg(clefs[k1], clefs[k2]) == 1)
    {
        printf("Les 2 clefs sont égaux\n");
    }
    else{
        printf("Les 2 clefs ne sont pas égaux\n");
    }

    // FERMETURE
    fclose(file);

    // LIBERATION
    for(int i = 0; i<NB_CLEF; i++)
    {
        free(clefs[i]->clef_hexa);
        free(clefs[i]);
    }

    return 0;
}