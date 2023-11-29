#include <stdio.h>
#include <stdlib.h>
#include "../headers/tasArbre.h"
#include <math.h>
#include <string.h>

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

Clef128* copy(Clef128* clef)
{
    Clef128* res = (Clef128*)malloc(sizeof(Clef128));
    res->b32_1 = clef->b32_1;
    res->b32_2 = clef->b32_2;
    res->b32_3 = clef->b32_3;
    res->b32_4 = clef->b32_4;
    res->clef_hexa = (char*)malloc(sizeof(char)*33);
    strcpy(res->clef_hexa, clef->clef_hexa);
    return res;
}

TasArbre* creerNoeud(Clef128* clef)
{
    TasArbre* noeud = initialisation();
    noeud->clef = copy(clef);
    noeud->hauteur += 1;
    noeud->noeud += 1;
    return noeud;
}

void echangeClef(Clef128* a, Clef128* b)
{
    Clef128 tmp = *a;
    *a = *b;
    *b = tmp;
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

void reequilibrageRemontee(TasArbre* tas)
{
    if(tas->parent == NULL)
    {
        //printf("ReequilibrageRemontee : Fin du tas\n");
        return;
    }
    if(inf(tas->clef,tas->parent->clef))
    {
        echangeClef(tas->clef,tas->parent->clef);
        reequilibrageRemontee(tas->parent);
    }
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

/*
void ajoutBis (TasArbre * tas, Clef128* clef, int V)
{
    // ARBRE VIDE
    if(tas->clef == NULL){
        tas->clef = copy(clef);
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
*/

void ajout (TasArbre * tas, Clef128* clef)
{
    // ARBRE VIDE
    if(tas->clef == NULL){
        tas->clef = copy(clef);
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
        reequilibrageRemontee(tas->fg);
        return;
    }
    else{
        if(tas->fd == NULL)
        {
            tas->fd = creerNoeud(clef);
            tas->fd->parent = tas;
            majNoeudAjout(tas);
            reequilibrageRemontee(tas->fd);
            return;
        }
    }

    if(tas->fg->noeud == pow(2,(tas->fg->hauteur))-1) // si le sous arbre gauche est rempli
    {
        if(tas->fd->noeud == pow(2,(tas->fd->hauteur))-1) // si le sous arbre droit est rempli
        {
            if(tas->fg->hauteur == tas->fd->hauteur) // si les feuilles sont au meme niveau
            {
                ajout(tas->fg,clef);
            }
            else{
                ajout(tas->fd,clef);
            }
        }
        else{
            ajout(tas->fd,clef);
        }
    }
    else{
        ajout(tas->fg,clef);
    }

}

TasArbre* ajoutsIteratifs(Clef128* clefs[], int len)
{
    TasArbre* tas = initialisation();
    for(int i = 0; i<len; i++)
    {
        ajout(tas, clefs[i]);
    }
    return tas;
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
        return (Clef128){0, 0, 0, 0, ""};
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

Element* ajoutListe(TasArbre* noeud)
{
    Element* elt = (Element*)malloc(sizeof(Element));
    elt->noeud = noeud;
    elt->suiv = NULL;
    return elt;
}

void deleteListe(Liste* liste)
{
    while(liste->tete != NULL)
    {
        Element* elt = liste->tete;
        liste->tete = liste->tete->suiv;
        free(elt);
    }
    free(liste);
}

TasArbre* construction(Clef128* clefs[], int len)
{
    Liste* liste = (Liste*)malloc(sizeof(Liste));
    TasArbre* premier = creerNoeud(clefs[0]);
    liste->tete = ajoutListe(premier);
    liste->queue = liste->tete;
    TasArbre* tas = liste->tete->noeud;
    for(int i = 1; i<len; i++)
    {
        if(liste->tete->noeud->fg == NULL)
        {
            liste->tete->noeud->fg = creerNoeud(clefs[i]);
            liste->queue->suiv = ajoutListe(liste->tete->noeud->fg);
            liste->queue = liste->queue->suiv;

        }else{
            if(liste->tete->noeud->fd == NULL)
            {
                liste->tete->noeud->fd = creerNoeud(clefs[i]);
                liste->queue->suiv = ajoutListe(liste->tete->noeud->fd);
                liste->queue = liste->queue->suiv;
                liste->tete = liste->tete->suiv;
            }
        }
    }
    reequilibrage(tas);
    return tas;
}

TasArbre* Union(TasArbre* tas1, TasArbre* tas2)
{
    Liste* newliste = (Liste*)malloc(sizeof(Liste));
    TasArbre* premier = creerNoeud(tas1->clef);
    newliste->tete = ajoutListe(premier);
    newliste->queue = newliste->tete;
    TasArbre* tasArenvoie = newliste->tete->noeud;

    Liste* tasAcopie = (Liste*)malloc(sizeof(Liste));
    tasAcopie->tete = ajoutListe(tas1);
    tasAcopie->queue = tasAcopie->tete;
    while(tasAcopie->tete != NULL)
    {
        if(tasAcopie->tete->noeud->fg)
        {
            tasAcopie->queue->suiv = ajoutListe(tasAcopie->tete->noeud->fg);
            tasAcopie->queue = tasAcopie->queue->suiv;
        }
        if(tasAcopie->tete->noeud->fd)
        {
            tasAcopie->queue->suiv = ajoutListe(tasAcopie->tete->noeud->fd);
            tasAcopie->queue = tasAcopie->queue->suiv;
        }

        tasAcopie->tete = tasAcopie->tete->suiv;
        if(tasAcopie->tete == NULL)
        {
            break;
        }

        if(newliste->tete->noeud->fg == NULL)
        {
            newliste->tete->noeud->fg = creerNoeud(tasAcopie->tete->noeud->clef);
            newliste->queue->suiv = ajoutListe(newliste->tete->noeud->fg);
            newliste->queue = newliste->queue->suiv;
        }else{
            if(newliste->tete->noeud->fd == NULL)
            {
                newliste->tete->noeud->fd = creerNoeud(tasAcopie->tete->noeud->clef);
                newliste->queue->suiv = ajoutListe(newliste->tete->noeud->fd);
                newliste->queue = newliste->queue->suiv;
                newliste->tete = newliste->tete->suiv;
            }
        }
    }

    Liste* tasAcopie2 = (Liste*)malloc(sizeof(Liste));
    tasAcopie2->tete = ajoutListe(tas2);
    tasAcopie2->queue = tasAcopie2->tete;
    while(tasAcopie2->tete != NULL)
    {
        if(tasAcopie2->tete->noeud->fg)
        {     
            tasAcopie2->queue->suiv = ajoutListe(tasAcopie2->tete->noeud->fg);
            tasAcopie2->queue = tasAcopie2->queue->suiv;
        }
        if(tasAcopie2->tete->noeud->fd)
        {
            tasAcopie2->queue->suiv = ajoutListe(tasAcopie2->tete->noeud->fd);
            tasAcopie2->queue = tasAcopie2->queue->suiv;
        }
    
        if(newliste->tete->noeud->fg == NULL)
        {
            newliste->tete->noeud->fg = creerNoeud(tasAcopie2->tete->noeud->clef);
            newliste->queue->suiv = ajoutListe(newliste->tete->noeud->fg);
            newliste->queue = newliste->queue->suiv;

        }else{
            if(newliste->tete->noeud->fd == NULL)
            {
                newliste->tete->noeud->fd = creerNoeud(tasAcopie2->tete->noeud->clef);
                newliste->queue->suiv = ajoutListe(newliste->tete->noeud->fd);
                newliste->queue = newliste->queue->suiv;
                newliste->tete = newliste->tete->suiv;
            }
        }
        tasAcopie2->tete = tasAcopie2->tete->suiv;
    }

    return tasArenvoie;
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

void delete(TasArbre* tas)
{
    if(tas == NULL)
    {
        return;
    }
    free(tas->clef->clef_hexa);
    free(tas->clef);
    delete(tas->fg);
    delete(tas->fd);
    free(tas);
}
