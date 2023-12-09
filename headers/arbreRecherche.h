#ifndef ARBRE_RECHERCHE_H
#define ARBRE_RECHERCHE_H

#include "clef128.h" 

typedef struct noeud {
    Clef128 * clef;
    struct noeud * gauche;
    struct noeud * droite;
    int hauteur;
} Noeud;

Noeud* creerNoeud(Clef128* cle);
Noeud* inserer(Noeud* noeud, Clef128* cle);
int rechercher(Noeud* racine, Clef128* cle);
Noeud* rotationDroite(Noeud* y);
Noeud* rotationGauche(Noeud* x);
int hauteur(Noeud* N);
int getBalanceFactor(Noeud* N);

#endif
