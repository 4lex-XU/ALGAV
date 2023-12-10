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
// complexité en O(log n)
void reequilibrerTas (TasTableau * tas, int i) 
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
    // Si le minimum a changé, on échange et on rééquilibre le sous-arbre
    if (min != i) {
        echanger(&tas->tab[i], &tas->tab[min]);
        reequilibrerTas(tas, min);
    }
}

Clef128 supprMinTasTableau (TasTableau * tas) 
{
    if (tas->taille == 0) { // Si le tas est vide on retourne clef vide
        printf("Tas vide\n");
        return (Clef128){0, 0, 0, 0, ""};
    }
    Clef128 min = tas->tab[0];
    tas->tab[0] = tas->tab[tas->taille-1];
    tas->taille--;
    reequilibrerTas(tas, 0);
    return min;
}

void ajoutTasTableau (TasTableau * tas, Clef128 clef) 
{
    if (tas->taille == tas->capacite) { // Si le tas est plein on double sa capacité
        tas->capacite *= 2;
        tas->tab = (Clef128*)realloc(tas->tab, sizeof(Clef128)*tas->capacite);
    }
    // On ajoute la clef à la fin du tableau
    int i = tas->taille;
    tas->tab[i] = clef;
    tas->taille++;
    // On remonte la clef à sa place
    while (i > 0 && inf(&clef, &tas->tab[(i-1)/2])) { // Tant que la clef est plus petite que son père
        echanger(&tas->tab[i], &tas->tab[(i-1)/2]); // On remonte la clef
        i = (i-1)/2;
    }
}

// Ajoute les clefs dans le tas une par une, méthode naïve
TasTableau * ajoutsIteratifsTasTableau (Clef128 * clefs[], int deb, int fin) 
{
    TasTableau * tas = initTas(fin-deb);
    for (int i = deb; i < fin; i++) {
        ajoutTasTableau(tas, *clefs[i]);
    }
    return tas;
}

// Construit un tas à partir d'un tableau de clefs, méthode plus efficace
TasTableau * constructionTasTableau (Clef128 * clefs[], int deb, int fin)
{
    int taille = fin-deb;
    TasTableau * tas = initTas(taille);
    for (int i = deb, j = 0; i < fin; i++, j++) {
        tas->tab[j] = *clefs[i];
        tas->taille++;
    }
    for (int i = (taille-1)/2; i >= 0; i--) {
        reequilibrerTas(tas, i);
    }
    return tas;
}

void affichageTasTableau(TasTableau* tas)
{
    if(tas->taille == 0)
    {
        printf("AffichageTasTableau : Tas vide\n");
        return;
    }
    for(int i = 0; i<tas->taille; i++)
    {   
        printf("%d : ", i  );
        affichageClef(&tas->tab[i]);
    }
}

TasTableau * UnionTasTableau(TasTableau *tas1, TasTableau *tas2) {
    if(tas1->taille == 0) return tas2;
    if(tas2->taille == 0) return tas1;

    int tailleTotale = tas1->taille + tas2->taille;
    TasTableau * tasUnion = initTas(tailleTotale);

    // Copie des éléments du tas 1 et 2 dans le nouveau tas
    for (int i = 0; i < tas1->taille; i++) {
        tasUnion->tab[i] = tas1->tab[i];
    }
    for (int i = 0; i < tas2->taille; i++) {
        tasUnion->tab[tas1->taille + i] = tas2->tab[i];
    }
    tasUnion->taille = tailleTotale;

    // rééquilibrage du nouveau tas
    for (int i = (tasUnion->taille / 2) - 1; i >= 0; i--) {
        reequilibrerTas(tasUnion, i);
    }
    return tasUnion;
}

void deleteTasTableau(TasTableau *tas) {
    free(tas->tab);
    free(tas);
}
