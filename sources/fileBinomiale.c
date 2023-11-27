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
    file->tournois = T->fils;
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

FileBinomiale * Reste(FileBinomiale * F) {
    if (EstVideFile(F)) return NULL;
    TournoiBinomiale * minTournoi = MinDeg(F);
    FileBinomiale * reste = (FileBinomiale *)malloc(sizeof(FileBinomiale));
    reste->tournois = F->tournois == minTournoi ? minTournoi->frere : F->tournois;

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

    // Inverser les fils du tournoi min pour former une nouvelle file
    FileBinomiale *fileTemp = (FileBinomiale *)malloc(sizeof(FileBinomiale));
    fileTemp->tournois = NULL;
    current = tournoiMin->fils;
    while (current != NULL) {
        TournoiBinomiale *next = current->frere;
        current->frere = fileTemp->tournois;
        current->pere = NULL;
        fileTemp->tournois = current;
        current = next;
    }

    // Fusionner la nouvelle file avec la file restante
    return Union(file, fileTemp);
}

FileBinomiale * ajout (FileBinomiale * F, TournoiBinomiale * T)
{
    if (EstVideFile(F))
    {
        FileBinomiale * file = (FileBinomiale*)malloc(sizeof(FileBinomiale));
        file->tournois = T;
        return file;
    }
    T->frere = F->tournois;
    F->tournois = T;
    return F;
}

FileBinomiale * construction (Clef128* clefs[], int deb, int fin)
{
    FileBinomiale * file = (FileBinomiale*)malloc(sizeof(FileBinomiale));
    file->tournois = NULL;
    for (int i = deb; i < fin; i++)
    {
        TournoiBinomiale * t = initTournoiBinomial(*clefs[i]);
        file = ajout(file, t);
    }
    return file;
}
FileBinomiale * Union(FileBinomiale * F1, FileBinomiale * F2)
{
    if (EstVideFile(F1)) return F2;
    if (EstVideFile(F2)) return F1;

    FileBinomiale *resultat = (FileBinomiale *)malloc(sizeof(FileBinomiale));
    resultat->tournois = NULL;
    TournoiBinomiale *T = NULL;

    while (!EstVideFile(F1) || !EstVideFile(F2) || T != NULL) {
        TournoiBinomiale *T1 = MinDeg(F1);
        TournoiBinomiale *T2 = MinDeg(F2);

        if (T == NULL) {
            if (Degre(T1) < Degre(T2)) {
                resultat = ajout(resultat, T1);
                F1 = Reste(F1);
            } else if (Degre(T2) < Degre(T1)) {
                resultat = ajout(resultat, T2);
                F2 = Reste(F2);
            } else {
                T = Union2Tid(T1, T2);
                F1 = Reste(F1);
                F2 = Reste(F2);
            }
        } else {
            if (EstVideFile(F1)) {
                resultat = Union(File(T), F2);
                T = NULL;
            } else if (EstVideFile(F2)) {
                resultat = Union(File(T), F1);
                T = NULL;
            } else if (Degre(T) < Degre(T1) && Degre(T) < Degre(T2)) {
                resultat = ajout(resultat, T);
                T = NULL;
            } else if (Degre(T) == Degre(T1) && Degre(T) == Degre(T2)) {
                resultat = ajout(Union(Reste(F1), Reste(F2)), T);
                T = Union2Tid(T1, T2);
            } else if (Degre(T) == Degre(T1) && Degre(T) < Degre(T2)) {
                T = Union2Tid(T1, T);
                F1 = Reste(F1);
            } else if (Degre(T) == Degre(T2) && Degre(T) < Degre(T1)) {
                T = Union2Tid(T2, T);
                F2 = Reste(F2);
            }
        }
    }

    return resultat;
}
