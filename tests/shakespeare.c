#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../headers/fonctionHachage.h"
#include "../headers/arbreRecherche.h"
#include "../headers/listeChaine.h"

#define MAX 1000
#define NBKEY 26588

int main()
{
    FILE * file = NULL;
    char * jeux[1] = 
    {   "./Shakespeare/1henryiv.txt"
    };

    // OUVERTURE
    //printf("%s\n", jeux[i]);
    if((file = fopen(jeux[1], "r")) == NULL)
    {
        printf("Error: not open\n");
        return 0;
    }

    char buffer[MAX];
    HashMap* map = NULL;
    HashMap* tmp;
    Noeud* arbre_rech = NULL;

    // LECTURE DES CLES DANS LE FICHIER
    while(fgets(buffer, MAX, file) != NULL)
    {
        unsigned int* md5 = MD5(buffer);
        Clef128* clef = (Clef128*)malloc(sizeof(Clef128));
        clef->clef_hexa = (char*)malloc(sizeof(char));
        clef->b32_1 = md5[3];
        clef->b32_2 = md5[2];
        clef->b32_3 = md5[1];
        clef->b32_4 = md5[0];
        strcpy(clef->clef_hexa, buffer);
        arbre_rech = inserer(arbre_rech, clef);

        if((tmp = findMap(map, buffer)) == NULL)
        {
            insertMap(map, buffer);
        }else{
            tmp->value++;
        }
    }

    afficheMap(map);

    fclose(file);
    return 0;
}