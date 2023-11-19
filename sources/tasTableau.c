#include <stdio.h>
#include <stdlib.h>
#include "../headers/tasTableau.h"

TasTableau * initTas(int capacite) 
{
    TasTableau * tas = (TasTableau*)malloc(sizeof(TasTableau));
    tas->taille = 0;
    tas->capacite = capacite;
    tas->tab = (Clef128*)malloc(sizeof(Clef128)*capacite);
    return tas;
}

void echanger (Clef128 * a, Clef128 * b) 
{
    Clef128 tmp = *a;
    *a = *b;
    *b = tmp;
}

// fonction récursive qui fait descendre le père à la bonne place
void tasMin (TasTableau * tas, int i) 
{
    int min = i;
    int gauche = 2*i+1;
    int droite = 2*i+2;
    if (gauche < tas->taille && inf(&tas->tab[gauche], &tas->tab[min])) {
        min = gauche;
    }
    if (droite < tas->taille && inf(&tas->tab[droite], &tas->tab[min])) {
        min = droite;
    }
    if (min != i) {
        echanger(&tas->tab[i], &tas->tab[min]);
        tasMin(tas, min);
    }
}

Clef128 supprMin (TasTableau * tas) 
{
    if (tas->taille == 0) { // Si le tas est vide on retourne clef vide
        printf("Tas vide\n");
        return (Clef128){0, 0, 0, 0};
    }
    Clef128 min = tas->tab[0];
    tas->tab[0] = tas->tab[tas->taille-1];
    tas->taille--;
    tasMin(tas, 0);
    return min;
}

void ajout (TasTableau * tas, Clef128 clef) 
{
    if (tas->taille == tas->capacite) { // Si le tas est plein on double sa capacité
        tas->capacite *= 2;
        tas->tab = (Clef128*)realloc(tas->tab, sizeof(Clef128)*tas->capacite);
    }
    tas->taille++;
    int i = tas->taille;
    tas->tab[i] = clef;
    while (i > 0 && inf(&clef, &tas->tab[(i-1)/2])) { // Tant que la clef est plus petite que son père
        echanger(&tas->tab[i], &tas->tab[(i-1)/2]); // On remonte la clef
        i = (i-1)/2;
    }
}

// Ajoute les clefs dans le tas une par une, méthode naïve
TasTableau * ajoutIteratifs (Clef128 clefs[], int taille) 
{
    TasTableau * tas = initTas(taille);
    for (int i = 0; i < taille; i++) {
        Ajout(tas, clefs[i]);
    }
    return tas;
}

// Construit un tas à partir d'un tableau de clefs, méthode plus efficace
TasTableau * construction (Clef128 clefs[], int taille)
{
    TasTableau * tas = (TasTableau*)malloc(sizeof(TasTableau)*taille);
    tas->taille = taille;
    tas->capacite = taille;
    tas->tab = clefs;
    for (int i = (taille-1)/2; i >= 0; i--) {
        tasMin(tas, i);
    }
    return tas;
}
