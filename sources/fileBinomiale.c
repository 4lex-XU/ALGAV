#include <stdio.h>
#include <stdlib.h>
#include "../headers/fileBinomiale.h"

int EstVide(TournoiBinomiale * T) 
{
    return T == NULL;
}

int Degre (TournoiBinomiale * T)
{
    if (!T) return -1;
    int degre = 0;
    TournoiBinomiale * current = T->fils;
    while (current)
    {
        degre++;
        current = current->frere;
    }
    return degre;
}

TournoiBinomiale * Union2Tid(TournoiBinomiale * T1, TournoiBinomiale * T2) 
{
    if (!T1 || !T2) return T1 ? T1 : T2;
    if (inf(&T2->clef, &T1->clef)) {
        // Échange T1 et T2
        TournoiBinomiale *temp = T1;
        T1 = T2;
        T2 = temp;
    }
    T2->pere = T1;
    T2->frere = T1->fils;
    T1->fils = T2;
    return T1;
}

FileBinomiale * Decapite(TournoiBinomiale * T) 
{
    FileBinomiale *file = (FileBinomiale *)malloc(sizeof(FileBinomiale));
    file->tournois = NULL;
    for(TournoiBinomiale *current = T->fils; current != NULL;) {
        TournoiBinomiale *next = current->frere;
        current->frere = file->tournois;
        current->pere = NULL;
        file->tournois = current;
        current = next;
    }
    free(T);
    return file;
}

FileBinomiale * File(TournoiBinomiale * T) 
{
    FileBinomiale *file = (FileBinomiale *)malloc(sizeof(FileBinomiale));
    file->tournois = T;
    return file;
}

TournoiBinomiale * initTournoiBinomial (Clef128 clef)
{
    TournoiBinomiale * t = (TournoiBinomiale*)malloc(sizeof(TournoiBinomiale));
    t->clef = clef;
    t->pere = NULL;
    t->fils = NULL;
    t->frere = NULL;
    return t;
}

void affichageTournoiBinomial(TournoiBinomiale * T)
{
    if (!T) return;
    affichageClef(&T->clef);
    TournoiBinomiale * current = T->fils;
    while (current)
    {
        affichageTournoiBinomial(current);
        current = current->frere;
    }
}

void affichageFileBinomiale(FileBinomiale * F)
{
    if (!F) return;
    TournoiBinomiale * current = F->tournois;
    printf("File Binomiale : \n");
    while (current)
    {
        printf("Tournoi de degre %d : \n", Degre(current));
        affichageTournoiBinomial(current);
        current = current->frere;
    }
}

int EstVideFile(FileBinomiale * F) 
{
    return F == NULL || F->tournois == NULL;
}

TournoiBinomiale * MinDeg(FileBinomiale * F) 
{
    if (EstVideFile(F)) return NULL;
    TournoiBinomiale * minTournoi = F->tournois;
    TournoiBinomiale * current = F->tournois->frere;

    while (current) {
        if (Degre(current) < Degre(minTournoi)) {
            minTournoi = current;
        }
        current = current->frere;
    }
    return minTournoi;
}

// Retourne la file sans le tournoi de degré minimum
FileBinomiale * Reste(FileBinomiale * F) {
    if (EstVideFile(F)) return NULL;
    TournoiBinomiale * minTournoi = MinDeg(F);
    FileBinomiale * reste = (FileBinomiale *)malloc(sizeof(FileBinomiale));
    // Si le tournoi min est le premier de la file
    reste->tournois = F->tournois == minTournoi ? F->tournois->frere : F->tournois;

    // Retirer le tournoi min de la file
    TournoiBinomiale * current = F->tournois;
    while (current && current->frere) {
        if (current->frere == minTournoi) {
            current->frere = minTournoi->frere;
            break;
        }
        current = current->frere;
    }

    return reste;
}

FileBinomiale * supprMin(FileBinomiale *file)
{
    if (EstVideFile(file)) return file;

    // Trouver le tournoi avec le minimum
    TournoiBinomiale *tournoiMin = file->tournois;
    TournoiBinomiale *prevMin = NULL;

    TournoiBinomiale *current = file->tournois;
    TournoiBinomiale *prev = NULL;

    // Parcourir la file pour trouver le tournoi min
    while (current != NULL) {
        if (inf(&current->clef, &tournoiMin->clef)) {
            tournoiMin = current;
            prevMin = prev;
        }
        prev = current;
        current = current->frere;
    }

    // Retirer le tournoi min de la file
    if (prevMin != NULL) {
        prevMin->frere = tournoiMin->frere;
    } else {
        file->tournois = tournoiMin->frere;
    }

    // Créer une nouvelle file avec les fils du tournoi min, décomposition du tournoi min
    FileBinomiale *fileTemp = Decapite(tournoiMin);
    printf("&----------------File temp : \n");
    affichageFileBinomiale(fileTemp);


    // Fusionner la nouvelle file avec la file restante
    return Union(file, fileTemp);
}

// ajout d'un tournoi dans la file
// complexité : O(log(n))
FileBinomiale * ajout (FileBinomiale * F, TournoiBinomiale * T)
{
    if (EstVideFile(F))
    {
        F = (FileBinomiale*)malloc(sizeof(FileBinomiale));
        F->tournois = T;
        return F;
    }
    // ajout en tete
    T->frere = F->tournois;
    F->tournois = T;
    // faire l'union des tournois de meme degre
    TournoiBinomiale * current = F->tournois;
    TournoiBinomiale * prev = NULL;
    TournoiBinomiale * next = current->frere;
    // on parcourt la file
    while (next)
    {
        // on passe au tournoi suivant si le degre est different 
        // ou si le degre est le meme mais qu'il y a un autre tournoi de meme degre
        if (Degre(current) != Degre(next) || (next->frere && Degre(next) == Degre(next->frere)))
        {
            prev = current;
            current = next;
        }
        // on fait l'union des tournois de meme degre
        // on supprime le tournoi qui n'est pas le plus petit
        else if (inf(&current->clef, &next->clef))
        {
            // on supprime le tournoi next de la file
            current->frere = next->frere;
            Union2Tid(current, next);
        }
        else
        {
            if (!prev)
            {
                // on supprime le tournoi current de la file
                F->tournois = next;
            }
            else
            {
                prev->frere = next;
            }
            Union2Tid(next, current);
            current = next;
        }
        next = current->frere;
    }
    return F;
}

FileBinomiale * construction (Clef128* clefs[], int deb, int fin)
{
    FileBinomiale * file = (FileBinomiale*)malloc(sizeof(FileBinomiale));
    file->tournois = NULL;
    for (int i = deb; i < fin; i++)
    {
        affichageClef(clefs[i]);
        TournoiBinomiale * t = initTournoiBinomial(*clefs[i]);
        file = ajout(file, t);
    }
    return file;
}

FileBinomiale * UFret(FileBinomiale * F1, FileBinomiale * F2, TournoiBinomiale * T)
{
    if(EstVide(T)) 
    {
        if(EstVideFile(F1)) return F2;
        if(EstVideFile(F2)) return F1;

        TournoiBinomiale * T1 = MinDeg(F1);
        TournoiBinomiale * T2 = MinDeg(F2);
        int degreT1 = Degre(T1);
        int degreT2 = Degre(T2);

        if(degreT1 < degreT2) 
        {
            FileBinomiale * F = Union(Reste(F1), F2);
            return ajout(F, T1);
        }
        else if(degreT2 < degreT1) 
        {
            FileBinomiale * F = Union(F1, Reste(F2));
            return ajout(F, T2);
        }
        else 
        {
            FileBinomiale * F1Reste = Reste(F1);
            FileBinomiale * F2Reste = Reste(F2);
            return UFret(F1Reste, F2Reste, Union2Tid(T1, T2));
        }
    }
    else 
    {
        if (EstVideFile(F1))
        {
            FileBinomiale * nouvelleFile = File(T);
            return Union(nouvelleFile, F2);
        } 

        if (EstVideFile(F2)) 
        {
            FileBinomiale * nouvelleFile = File(T);
            return Union(nouvelleFile, F1);
        }

        TournoiBinomiale * T1 = MinDeg(F1);
        TournoiBinomiale * T2 = MinDeg(F2);

        if (Degre(T) < Degre(T1) && Degre(T) < Degre(T2))
        {
            return ajout(Union(F1, F2), T);
        }
        if (Degre(T) == Degre(T1) && Degre(T) == Degre(T2))
        {
            FileBinomiale * F1Reste = Reste(F1);
            FileBinomiale * F2Reste = Reste(F2);
            return ajout(UFret(F1Reste, F2Reste, Union2Tid(T1, T2)), T);
        }
        if (Degre(T) == Degre(T1) && Degre(T) < Degre(T2))
        {
            FileBinomiale * F1Reste = Reste(F1);
            return UFret(F1Reste, F2, Union2Tid(T1, T));
        }
        if (Degre(T) == Degre(T2) && Degre(T) < Degre(T1))
        {
            FileBinomiale * F2Eeste = Reste(F2);
            return UFret(F1, F2Eeste, Union2Tid(T2, T));
        }
    }
    return NULL;
}

FileBinomiale * Union(FileBinomiale * F1, FileBinomiale * F2)
{
    return UFret(F1, F2, NULL);
}

void delete(TournoiBinomiale * T)
{
    if (!T) return;
    TournoiBinomiale * current = T->fils;
    while (current)
    {
        TournoiBinomiale * next = current->frere;
        delete(current);
        current = next;
    }
    free(T);
}

void deleteFile(FileBinomiale * F)
{
    if (!F) return;
    TournoiBinomiale * current = F->tournois;
    while (current)
    {
        TournoiBinomiale * next = current->frere;
        delete(current);
        current = next;
    }
    free(F);
}