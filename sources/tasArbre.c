#include <stdio.h>
#include <stdlib.h>
#include "../headers/tasArbre.h"
#include <math.h>

TasArbre* initialisation()
{
    TasArbre* newTas = (TasArbre*)malloc(sizeof(TasArbre));
    newTas->clef = NULL;
    newTas->fd = NULL;
    newTas->fg = NULL;
    newTas->parent = NULL; 
    newTas->hauteur = 0;
    newTas->noeud = 0;
    return newTas;
}

TasArbre* creerNoeud(Clef128* clef)
{
    TasArbre* noeud = (TasArbre*)malloc(sizeof(TasArbre));
    noeud->clef = clef;
    noeud->fd = NULL;
    noeud->fg = NULL;
    noeud->parent = NULL;
    noeud->hauteur = 1;
    noeud->noeud = 1;
    return noeud;
}

void echangeClef(Clef128* a, Clef128* b)
{
    Clef128 tmp = *a;
    *a = *b;
    *b = tmp;
}

void majHauteurAjout(TasArbre* tas)
{
    // ARRIVEE A LA RACINE
    if(tas == NULL)
    {
        //printf("MajHauteur Ajout : racine\n");
        return;
    }
    int hauteurG = (tas->fg == NULL ? 0 : tas->fg->hauteur);
    int hauteurD = (tas->fd == NULL ? 0 : tas->fd->hauteur);
    // MAJ HAUTEUR
    tas->hauteur = 1 + (hauteurG>hauteurD ? hauteurG : hauteurD);
    // APPEL RECURSIF SUR TOUS LES PARENTS DU NOEUDS
    majHauteurAjout(tas->parent);
}

void majNoeudAjout(TasArbre* tas)
{
    // ARRIVEE A LA RACINE
    if(tas == NULL)
    {
        //printf("MajNoeud Ajout : racine\n");
        return;
    }
    // MAJ NOEUD
    tas->noeud ++;
    // APPEL RECURSIF SUR TOUS LES PARENTS DU NOEUDS
    majNoeudAjout(tas->parent);
}

void ajout (TasArbre * tas, Clef128* clef, int V)
{
    // ARBRE VIDE
    if(tas->clef == NULL){
        tas->clef = clef;
        tas->hauteur += 1;
        tas->noeud += 1;
        return;
    }
    // CLEF EXISTANT
    if(eg(tas->clef, clef)){
        printf("La clef est déjà dans le tas\n");
        return;
    }

    // INSERTION
    if(tas->fg == NULL)
    {
        tas->fg = creerNoeud(clef);
        tas->fg->parent = tas;
        majHauteurAjout(tas);
        majNoeudAjout(tas);
        if(inf(clef, tas->clef) && V)
        {
            echangeClef(tas->clef, clef);
        }
        return;
    }
    else{
        if(tas->fd == NULL)
        {
            tas->fd = creerNoeud(clef);
            tas->fd->parent = tas;
            majNoeudAjout(tas);
            if(inf(clef, tas->clef) && V)
            {
                echangeClef(tas->clef, clef);
            }
            return;
        }
    }

    if(tas->fg->noeud == pow(2,(tas->fg->hauteur))-1) // si le sous arbre gauche est rempli
    {
        if(tas->fd->noeud == pow(2,(tas->fd->hauteur))-1) // si le sous arbre droit est rempli
        {
            if(tas->fg->hauteur == tas->fd->hauteur) // si les feuilles sont au meme niveau
            {
                if(inf(clef, tas->clef) && V)
                {
                    echangeClef(tas->clef, clef);
                }
                ajout(tas->fg,clef,V);
            }
            else{
                if(inf(clef, tas->clef) && V)
                {
                    echangeClef(tas->clef, clef);
                }
                ajout(tas->fd,clef,V);
            }
        }
        else{
            if(inf(clef, tas->clef) && V)
            {
                echangeClef(tas->clef, clef);
            }
            ajout(tas->fd,clef,V);
        }
    }
    else{
        if(inf(clef, tas->clef) && V)
        {
            echangeClef(tas->clef, clef);
        }
        ajout(tas->fg,clef,V);
    }

}

void affichageTasArbre(TasArbre* tas) // Parcours prefixe
{
    if(tas->clef == NULL)
    {
        printf("AffichageTasArbre : Tas vide\n");
        return;
    }
    affichageClef(tas->clef);
    printf("hauteur = %d\n", tas->hauteur);
    printf("noeud = %d\n", tas->noeud);
    if(tas->fg != NULL)
    {
        printf("-------GAUCHE--------\n");
        affichageTasArbre(tas->fg);
    }
    if(tas->fd != NULL)
    {
        printf("-------DROIT--------\n");
        affichageTasArbre(tas->fd);
    }
}

TasArbre* ajoutsIteratifs(Clef128* clefs[], int len, int V)
{
    TasArbre* tas = initialisation();
    for(int i = 0; i<len; i++)
    {
        ajout(tas, clefs[i], V);
    }
    return tas;
}

void echangeRacine(TasArbre* tas)
{
    // RACINE
    if(tas->fg == NULL && tas->fd == NULL)
    {
        //printf("Echange Racine : Fin du tas\n");
        return;
    }
    // PAS DE SOUS ARBRE DROIT
    if(tas->fd == NULL)
    {
        if(inf(tas->fg->clef,tas->clef))
        {
            echangeClef(tas->fg->clef,tas->clef);
        }
    }else{ // SI 2 FILS : GAUCHE ET DROIT
        if(inf(tas->fg->clef,tas->fd->clef)) // TEST CLEF PLUS PETIT ENTRE LES 2 SOUS ARBRES
        {
           if(inf(tas->fg->clef,tas->clef)) // SI LE SOUS ARBRE GAUCHE EST PLUS PETIT -> TEST SI PLUS PETIT QUE NOUVEAU RACINE
            {
                echangeClef(tas->fg->clef,tas->clef);
                echangeRacine(tas->fg);
            }
        }else{
            if(inf(tas->fd->clef,tas->clef)) // SI LE SOUS ARBRE DROIT EST PLUS PETIT -> TEST SI PLUS PETIT QUE NOUVEAU RACINE
            {
                echangeClef(tas->fd->clef,tas->clef);
                echangeRacine(tas->fd);
            }
        }
    }
}

void majHauteurSuppr(TasArbre* tas)
{
    // ARRIVEE A LA RACINE
    if(tas == NULL)
    {
        //printf("MajHauteur Suppr : racine\n");
        return;
    }
    int hauteurG = (tas->fg == NULL ? 0 : tas->fg->hauteur);
    int hauteurD = (tas->fd == NULL ? 0 : tas->fd->hauteur);
    // MAJ HAUTEUR
    tas->hauteur = 1 + (hauteurG>hauteurD ? hauteurG : hauteurD);
    // APPEL RECURSIF SUR TOUS LES PARENTS DU NOEUDS
    majHauteurSuppr(tas->parent);
}

void majNoeudSuppr(TasArbre* tas)
{
    // ARRIVEE A LA RACINE
    if(tas == NULL)
    {
        //printf("MajNoeud Suppr : racine\n");
        return;
    }
    // MAJ NOEUD
    tas->noeud --;
    // APPEL RECURSIF SUR TOUS LES PARENTS DU NOEUDS
    majNoeudSuppr(tas->parent);
}

Clef128 supprMin (TasArbre* tas, TasArbre* racine) 
{
    Clef128 tmp = *racine->clef;
    TasArbre* dernier = NULL;

    // TAS VIDE
    if(tas->clef == NULL && dernier == NULL)
    {
        printf("SuppMin : Tas vide\n");
        return (Clef128){0, 0, 0, 0};
    }

    if(tas->fg == NULL && dernier == NULL) // 1 noeud 
    {
        tas->clef = NULL;
        tas->hauteur = 0;
        tas->noeud = 0;
        return tmp;
    }
    else{
        if(tas->fd == NULL) // 2 noeuds
        {
            dernier = tas->fg;
            tas->fg = NULL;
            majHauteurSuppr(tas);
            majNoeudSuppr(tas);
        }
        else{
            if(tas->fd->fg == NULL && tas->fd->fd == NULL && tas->fg->hauteur == tas->fd->hauteur) // 3 noeuds
            {
                dernier = tas->fd;
                tas->fd = NULL;
                majNoeudSuppr(tas);
            }
            else{
                if(tas->fg->noeud == pow(2,(tas->fg->hauteur))-1) // si le sous arbre gauche est rempli
                {
                    if(tas->fd->noeud == pow(2,(tas->fd->hauteur))-1) // si le sous arbre droit est rempli
                    {
                        if(tas->fg->hauteur == tas->fd->hauteur) // si les feuilles sont au meme niveau
                        {
                            supprMin(tas->fd, racine);
                        }
                        else{
                            supprMin(tas->fg, racine);
                        }
                    }
                    else{
                        supprMin(tas->fd, racine);
                    }
                }
                else{
                    supprMin(tas->fg, racine);
                }
            }
        }
    }
    
    if(dernier)
    {
        echangeClef(racine->clef,dernier->clef);
        echangeRacine(racine);
    }

    return tmp;
}

void reequilibrage(TasArbre* tas)
{
    if(tas == NULL)
    {
        //printf("Reequilibrage : Fin du tas\n");
        return;
    }
    reequilibrage(tas->fg);
    reequilibrage(tas->fd);
    echangeRacine(tas);
}

TasArbre* construction(Clef128* clefs[], int len)
{
    TasArbre* tas = initialisation();
    for(int i = 0; i<len; i++)
    {
        ajout(tas, clefs[i], 0);
    }

    reequilibrage(tas);
    return tas;
}

void Union(TasArbre* tasUnion, TasArbre* tas1, TasArbre* tas2)
{
    if(tas1 != NULL)
    {
        ajout(tasUnion, tas1->clef, 0);
        Union(tasUnion, tas1->fg, tas2);
        Union(tasUnion, tas1->fd, tas2);
    }
    
    if(tas2 != NULL)
    {
        ajout(tasUnion, tas2->clef, 0);
        Union(tasUnion, tas1, tas2->fg);
        Union(tasUnion, tas1, tas2->fd);
    }
    reequilibrage(tasUnion);
}
