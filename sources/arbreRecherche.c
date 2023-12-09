#include "../headers/arbreRecherche.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

Noeud* creerNoeud(Clef128* clef) {
    Noeud* noeud = (Noeud*)malloc(sizeof(Noeud));
    noeud->clef = clef;
    noeud->gauche = NULL;
    noeud->droite = NULL;
    return noeud;
}

Noeud* inserer(Noeud* noeud, Clef128* clef) {
    if (noeud == NULL) return creerNoeud(clef);

    if (inf(clef, noeud->clef))
        noeud->gauche = inserer(noeud->gauche, clef);
    else if (inf(noeud->clef, clef))
        noeud->droite = inserer(noeud->droite, clef);
    else 
        return noeud;

    noeud->hauteur = 1 + max(hauteur(noeud->gauche), hauteur(noeud->droite));
    int equilibre = getBalanceFactor(noeud);

    // Cas Gauche Gauche
    if (equilibre > 1 && inf(clef, noeud->gauche->clef))
        return rotationDroite(noeud);

    // Cas Droite Droite
    if (equilibre < -1 && inf(noeud->droite->clef, clef))
        return rotationGauche(noeud);

    // Cas Gauche Droite
    if (equilibre > 1 && inf(noeud->gauche->clef, clef)) {
        noeud->gauche = rotationGauche(noeud->gauche);
        return rotationDroite(noeud);
    }

    // Cas Droite Gauche
    if (equilibre < -1 && inf(clef, noeud->droite->clef)) {
        noeud->droite = rotationDroite(noeud->droite);
        return rotationGauche(noeud);
    }

    return noeud;
}

int rechercher(Noeud* racine, Clef128* clef) {
    if (racine == NULL)
        return 0;
    
    if (eg(racine->clef, clef))
        return 1;

    if (inf(racine->clef, clef))
        return rechercher(racine->droite, clef);

    return rechercher(racine->gauche, clef);
}

int hauteur(Noeud *N) {
    if (N == NULL)
        return 0;
    return N->hauteur;
}

Noeud * rotationDroite(Noeud *y) {
    Noeud *x = y->gauche;
    Noeud *T2 = x->droite;

    // Effectuer la rotation
    x->droite = y;
    y->gauche = T2;

    // Mettre à jour les hauteurs
    y->hauteur = max(hauteur(y->gauche), hauteur(y->droite)) + 1;
    x->hauteur = max(hauteur(x->gauche), hauteur(x->droite)) + 1;

    // Retourner la nouvelle racine
    return x;
}


Noeud* rotationGauche(Noeud *x) {
    Noeud *y = x->droite;
    Noeud *T2 = y->gauche;

    // Effectuer la rotation
    y->gauche = x;
    x->droite = T2;

    // Mettre à jour les hauteurs
    x->hauteur = max(hauteur(x->gauche), hauteur(x->droite)) + 1;
    y->hauteur = max(hauteur(y->gauche), hauteur(y->droite)) + 1;

    // Retourner la nouvelle racine
    return y;
}


int getBalanceFactor(Noeud * N) {
    if (N == NULL)
        return 0;
    return hauteur(N->gauche) - hauteur(N->droite);
}

int main () {
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
    
    return 0;
}