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
  
    TasArbre* t1 = (TasArbre*)malloc(sizeof(TasArbre));
    t1->clef = NULL;
    t1->fd = NULL;
    t1->fg = NULL; 
    t1->hauteur = 0;
    t1->noeud = 0;

    /*
    ajout(t1, clefs[0]);

    affichageClef(t1->clef);
    printf("hauteur = %d\n", t1->hauteur);
    printf("noeud = %d\n", t1->noeud);

    ajout(t1, clefs[1]);

    affichageClef(t1->clef);
    printf("hauteur = %d\n", t1->hauteur);
    printf("noeud = %d\n", t1->noeud);

    affichageClef(t1->fg->clef);
    printf("hauteur = %d\n", t1->fg->hauteur);
    printf("noeud = %d\n", t1->fg->noeud);

    ajout(t1, clefs[2]);

    affichageClef(t1->clef);
    printf("hauteur = %d\n", t1->hauteur);
    printf("noeud = %d\n", t1->noeud);

    affichageClef(t1->fg->clef);
    printf("hauteur = %d\n", t1->fg->hauteur);
    printf("noeud = %d\n", t1->fg->noeud);

    affichageClef(t1->fd->clef);
    printf("hauteur = %d\n", t1->fd->hauteur);
    printf("noeud = %d\n", t1->fd->noeud);
    
    ajout(t1, clefs[3]);

    affichageClef(t1->clef);
    printf("hauteur = %d\n", t1->hauteur);
    printf("noeud = %d\n", t1->noeud);

    affichageClef(t1->fg->clef);
    printf("hauteur = %d\n", t1->fg->hauteur);
    printf("noeud = %d\n", t1->fg->noeud);

    affichageClef(t1->fd->clef);
    printf("hauteur = %d\n", t1->fd->hauteur);
    printf("noeud = %d\n", t1->fd->noeud);
    */

    ajout(t1, clefs[0]);
    ajout(t1, clefs[1]);
    ajout(t1, clefs[2]);
    ajout(t1, clefs[3]);
    ajout(t1, clefs[4]);
    ajout(t1, clefs[5]);
    ajout(t1, clefs[6]);
    ajout(t1, clefs[7]);
    ajout(t1, clefs[8]);
    affichageTasArbre(t1);

    return 0;
}