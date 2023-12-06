#include <stdio.h>
#include <stdlib.h>
#include "../headers/fileBinomiale.h"

TournoiBinomial * Tournoi (Clef128 clef)
{
    TournoiBinomial * T = (TournoiBinomial *)malloc(sizeof(TournoiBinomial));
    T->clef = clef;
    T->degre = 0;
    T->fils = NULL;
    T->frere = NULL;
    return T;
}

FileBinomiale * File(TournoiBinomial * T) 
{
    FileBinomiale *file = (FileBinomiale *)malloc(sizeof(FileBinomiale));
    file->tete = (ElementFile *)malloc(sizeof(ElementFile));
    file->tete->tournoi = T;
    file->tete->suivant = NULL;
    file->queue = file->tete;
    return file;
}

int EstVideTournoi(TournoiBinomial * T) 
{
    return T == NULL;
}

int EstVideFile(FileBinomiale * F) 
{
    return F == NULL || F->tete == NULL;   
}

int Degre(TournoiBinomial * T) 
{
    return T ? T->degre : -1;
}

TournoiBinomial * MinDeg(FileBinomiale * F) 
{
    if (EstVideFile(F)) return NULL;
    TournoiBinomial * minTournoi = F->tete->tournoi;
    ElementFile * current = F->tete->suivant;

    while (current) {
        if (Degre(current->tournoi) < Degre(minTournoi)) {
            minTournoi = current->tournoi;
        }
        current = current->suivant;
    }
    return minTournoi;
}

FileBinomiale * Decapite(TournoiBinomial * T) 
{
    TournoiBinomial * current = T->fils->frere;
    T->fils->frere = NULL;
    FileBinomiale * file = File(T->fils);
    while (current) {
        TournoiBinomial * temp = current->frere;
        current->frere = NULL;
        file = AjoutMin(file, current);
        current = temp;
    }
    //free(T);
    return file;
}

// Retourne la file sans le tournoi de degré minimum
FileBinomiale * Reste(FileBinomiale * F) 
{
    if (EstVideFile(F)) return NULL;
    FileBinomiale * reste = (FileBinomiale *)malloc(sizeof(FileBinomiale));
    reste->tete = F->tete->suivant;
    reste->queue = F->queue;
    return reste;
}

TournoiBinomial * Union2Tid(TournoiBinomial * T1, TournoiBinomial * T2) 
{
    if (EstVideTournoi(T1)) return T2;
    if (EstVideTournoi(T2)) return T1;

    // On met le tournoi de plus petit degré en fils du tournoi de plus grand degré
    if (inf(&T2->clef, &T1->clef)) {
        TournoiBinomial * temp = T1;
        T1 = T2;
        T2 = temp;
    }
    T2->frere = T1->fils;
    T1->fils = T2;
    T1->degre++;
    return T1;
}

FileBinomiale * Equilibrage(FileBinomiale * F) 
{
    if (EstVideFile(F)) return F;

    // faire l'union des tournois de meme degre
    ElementFile * current = F->tete;
    ElementFile * next = current->suivant;
    ElementFile * prev = NULL;
    // on parcourt la file
    while (next)
    {
        // on passe au tournoi suivant si le degre est different 
        // ou si le degre est le meme mais qu'il y a un autre tournoi de meme degre
        if (Degre(current->tournoi) != Degre(next->tournoi) || (next->suivant && Degre(next->tournoi) == Degre(next->suivant->tournoi)))
        {
            prev = current;
            current = next;
        }
        // on fait l'union des tournois de meme degre
        // on supprime le tournoi qui n'est pas le plus petit
        else if (inf(&current->tournoi->clef, &next->tournoi->clef))
        {
            // on supprime le tournoi next de la file
            current->suivant = next->suivant;
            current->tournoi = Union2Tid(current->tournoi, next->tournoi);
        }
        else
        {
            if (!prev)
            {
                // on supprime le tournoi current de la file
                F->tete = next;
            }
            else
            {
                prev->suivant = next;
            }
            next->tournoi = Union2Tid(current->tournoi, next->tournoi);
            current = next;
        }
        next = current->suivant;
    }
    return F;
}

FileBinomiale * AjoutMin(FileBinomiale * F, TournoiBinomial * T) 
{
    if (EstVideFile(F))
    {
        F = File(T);
        return F;
    }
    // ajout en tete
    ElementFile * newElement = (ElementFile *)malloc(sizeof(ElementFile));
    newElement->tournoi = T;
    newElement->suivant = F->tete;
    F->tete = newElement;
    return Equilibrage(F);
}

TournoiBinomial * TournoiMin(FileBinomiale * F) 
{
    // Trouver le tournoi avec le minimum
    ElementFile * current = F->tete;
    ElementFile * prev = NULL;
    ElementFile * prevMin = NULL;
    ElementFile * tournoiMin = current;

    // Parcourir la file pour trouver le tournoi min
    while (current) {
        if (inf(&current->tournoi->clef, &tournoiMin->tournoi->clef)) {
            tournoiMin = current;
            prevMin = prev;
        }
        prev = current;
        current = current->suivant;
    }

    // Retirer le tournoi min de la file
    if (prevMin != NULL) {
        prevMin->suivant = tournoiMin->suivant;
    } else {
        F->tete = tournoiMin->suivant;
    }
    return tournoiMin->tournoi;
}

FileBinomiale * SupprMin(FileBinomiale * F) 
{
    if (EstVideFile(F)) return F;

    // Trouver le tournoi avec le minimum
    TournoiBinomial * tournoiMin = TournoiMin(F);

    // Créer une nouvelle file avec les fils du tournoi min, décomposition du tournoi min
    FileBinomiale *fileTemp = Decapite(tournoiMin);

    // Fusionner la nouvelle file avec la file restante
    return Union(F, fileTemp);
}

FileBinomiale * Construction (Clef128 ** clefs, int debut, int fin)
{
    FileBinomiale * F = NULL;
    for (int i = debut; i < fin; i++)
    {
        TournoiBinomial * T = Tournoi(*clefs[i]);
        F = AjoutMin(F, T);
    }
    return F;
}

FileBinomiale * UFret(FileBinomiale * F1, FileBinomiale * F2, TournoiBinomial * T)
{
    if(EstVideTournoi(T)) 
    {
        if(EstVideFile(F1)) return F2;
        if(EstVideFile(F2)) return F1;

        TournoiBinomial * T1 = MinDeg(F1);
        TournoiBinomial * T2 = MinDeg(F2);
        int degreT1 = Degre(T1);
        int degreT2 = Degre(T2);

        if(degreT1 < degreT2) 
        {
            FileBinomiale * F = Union(Reste(F1), F2);
            return AjoutMin(F, T1);
        }
        else if(degreT2 < degreT1) 
        {
            FileBinomiale * F = Union(F1, Reste(F2));
            return AjoutMin(F, T2);
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

        TournoiBinomial * T1 = MinDeg(F1);
        TournoiBinomial * T2 = MinDeg(F2);

        if (Degre(T) < Degre(T1) && Degre(T) < Degre(T2))
        {
            return AjoutMin(Union(F1, F2), T);
        }
        if (Degre(T) == Degre(T1) && Degre(T) == Degre(T2))
        {
            FileBinomiale * F1Reste = Reste(F1);
            FileBinomiale * F2Reste = Reste(F2);
            return AjoutMin(UFret(F1Reste, F2Reste, Union2Tid(T1, T2)), T);
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

void affichageTournoiBinomial(TournoiBinomial * T)
{
    if (!T) return;
    affichageClef(&T->clef);
    TournoiBinomial * current = T->fils;
    while (current)
    {
        affichageTournoiBinomial(current);
        current = current->frere;
    }
}

void affichageFileBinomiale(FileBinomiale * F)
{
    if (!F) return;
    ElementFile * current = F->tete;
    printf("-------FILE BINOMIALE--------\n");
    while (current)
    {
        TournoiBinomial * currentTournoi = current->tournoi;
        printf("Tournoi de degre %d : \n", Degre(currentTournoi));
        affichageTournoiBinomial(currentTournoi);
        current = current->suivant;
    }
}

void deleteTournoiBinomial(TournoiBinomial * T)
{
    if (!T) return;
    TournoiBinomial * current = T->fils;
    while (current)
    {
        TournoiBinomial * temp = current->frere;
        deleteTournoiBinomial(current);
        current = temp;
    }
    free(T);
}

void deleteElementFile(ElementFile * E)
{
    if (!E) return;
    deleteTournoiBinomial(E->tournoi);
    free(E);
}

void deleteFileBinomiale(FileBinomiale * F)
{
    if (!F) return;
    ElementFile * current = F->tete;
    while (current)
    {
        ElementFile * temp = current->suivant;
        deleteElementFile(current);
        current = temp;
    }
    free(F);
}