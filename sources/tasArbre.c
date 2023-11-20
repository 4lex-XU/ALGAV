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

TasArbre* ajoutsIteratifs(Clef128* clefs[], int len)
{
    TasArbre* t = (TasArbre*)malloc(sizeof(TasArbre));
    t->clef = NULL;
    t->fd = NULL;
    t->fg = NULL; 
    t->hauteur = 0;
    t->noeud = 0;
    for(int i = 0; i<len; i++)
    {
        ajout(t,clefs[i]);
    }
    return t;
}

void comparaison(TasArbre* t)
{
    if(t->fg == NULL)
    {
        printf("Comparaison : Fin du tas\n");
        return;
    }
    if(inf(t->fg->clef,t->clef))
    {
        echange(t->fg->clef,t->clef);
        comparaison(t->fg);
    }
    else{
        if(t->fd == NULL)
        {
            printf("Comparaison : Fin du tas\n");
            return;
        }
        if(inf(t->fd->clef,t->clef))
        {
            echange(t->fd->clef,t->clef);
            comparaison(t->fd);
        }
    }
}

Clef128 supprMin (TasArbre* tas) 
{
    printf("ICI\n");
    Clef128 tmp;
    TasArbre* dernier = NULL;

    // TAS VIDE
    if(tas->clef == NULL && dernier == NULL)
    {
        printf("SuppMin : Tas vide\n");
        return (Clef128){0, 0, 0, 0};
    }

    if(tas->fg == NULL && dernier == NULL) // 1 noeud 
    {
        tmp = *tas->clef;
        tas->clef = NULL;
        tas->hauteur = 0;
        tas->noeud = 0;
        return tmp;
    }
    else{
        if(tas->fd == NULL) // 2 noeuds
        {
            printf("aaaaaaaaaaaa\n");
            dernier = tas->fg;
            printf("---------------------\n");
            affichageClef(dernier->clef);
            printf("---------------------\n");
            tas->fg = NULL;
            tas->hauteur --;
            tas->noeud --;
        }
        else{
            if(tas->fd->fg == NULL && tas->fd->fd == NULL && tas->fg->hauteur == tas->fd->hauteur) // 3 noeuds
            {
                printf("bbbbbbb\n");
                dernier = tas->fd;
                tas->fd = NULL;
                tas->noeud --;
            }
            else{
                if(tas->fg->noeud == pow(2,(tas->fg->hauteur))-1) // si le sous arbre gauche est rempli
                {
                    if(tas->fd->noeud == pow(2,(tas->fd->hauteur))-1) // si le sous arbre droit est rempli
                    {
                        if(tas->fg->hauteur == tas->fd->hauteur) // si les feuilles sont au meme niveau
                        {
                            printf("eeeeeeeeee\n");
                            supprMin(tas->fd);
                        }
                        else{
                            printf("ffffffffffff\n");
                            supprMin(tas->fg);
                        }
                    }
                    else{
                        printf("gggggggggggg\n");
                        supprMin(tas->fd);
                    }
                }
                else{
                    printf("hhhhhhhhhhhhh\n");
                    supprMin(tas->fg);
                }
            }
        }
    }
    
    if(dernier)
    {
        printf("iiiiiiiiiiiii\n");
        printf("---------------------\n");
        affichageClef(dernier->clef);
        printf("---------------------\n");

        tmp = *tas->clef;
        //pb = ne prends pas la racine du tas initial
        printf("---------------------\n");
        affichageClef(&tmp);
        printf("---------------------\n");

        echange(tas->clef,dernier->clef);
        printf("jjjjjjjjjjj\n");
        comparaison(tas);
        printf("kkkkkkkkkk\n");
    }

    return tmp;
}
