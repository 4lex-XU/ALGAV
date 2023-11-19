#include <stdio.h>
#include <stdlib.h>
#include "../headers/tasArbre.h"
#include <math.h>

void initialisation(TasArbre* t)
{
    t = (TasArbre*)malloc(sizeof(TasArbre));
    t->clef = NULL;
    t->fd = NULL;
    t->fg = NULL; 
    t->hauteur = 0;
    t->noeud = 0;
}

TasArbre* creerNoeud(Clef128* clef)
{
    TasArbre* noeud = (TasArbre*)malloc(sizeof(TasArbre));
    noeud->clef = clef;
    noeud->fd = NULL;
    noeud->fg = NULL;
    noeud->hauteur = 1;
    noeud->noeud = 1;
    return noeud;
}

void echange(Clef128* a, Clef128* b)
{
    Clef128 tmp = *a;
    *a = *b;
    *b = tmp;
}

void ajout (TasArbre * tas, Clef128* clef)
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
    }

    // INSERTION
    if(tas->fg == NULL)
    {
        tas->fg = creerNoeud(clef);
        tas->hauteur += 1;
        tas->noeud += 1;
        if(inf(clef, tas->clef))
        {
            echange(tas->clef, clef);
        }
        return;
    }
    else{
        if(tas->fd == NULL)
        {
            tas->fd = creerNoeud(clef);
            tas->noeud += 1;
            if(inf(clef, tas->clef))
            {
                echange(tas->clef, clef);
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
                if(inf(clef, tas->clef))
                {
                    echange(tas->clef, clef);
                }
                ajout(tas->fg,clef);
            }
            else{
                if(inf(clef, tas->clef))
                {
                    echange(tas->clef, clef);
                }
                ajout(tas->fd,clef);
            }
        }
        else{
            if(inf(clef, tas->clef))
            {
                echange(tas->clef, clef);
            }
            ajout(tas->fd,clef);
        }
    }
    else{
        if(inf(clef, tas->clef))
        {
            echange(tas->clef, clef);
        }
        ajout(tas->fg,clef);
    }

}

void affichageTasArbre(TasArbre* tas)
{
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

void supprMin (TasArbre * tas) 
{

}

void ajoutsIteratifs(Clef128 clefs[])
{

}
