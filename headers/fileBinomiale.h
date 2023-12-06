#include "clef128.h"
#ifndef H_FILEBINOMIALE
#define H_FILEBINOMIALE

typedef struct tournoiBinomial
{
    Clef128 clef;
    int degre;
    struct tournoiBinomial * fils;
    struct tournoiBinomial * frere; // frere droit
} TournoiBinomial;

typedef struct elementFile
{
    TournoiBinomial * tournoi;
    struct elementFile * suivant;
} ElementFile;

typedef struct fileBinomiale 
{
    ElementFile * tete;
    ElementFile * queue;
} FileBinomiale;

TournoiBinomial * Tournoi (Clef128 clef);
FileBinomiale * File(TournoiBinomial * T);
int EstVideTournoi(TournoiBinomial * T);
int EstVideFile(FileBinomiale * F);
int Degre(TournoiBinomial * T);
TournoiBinomial * MinDeg(FileBinomiale * F);
FileBinomiale * Decapite(TournoiBinomial * T);
FileBinomiale * Reste(FileBinomiale * F);
TournoiBinomial * Union2Tid(TournoiBinomial * T1, TournoiBinomial * T2);
FileBinomiale * Equilibrage(FileBinomiale * F);
FileBinomiale * AjoutMin(FileBinomiale * F, TournoiBinomial * T);
TournoiBinomial * TournoiMin(FileBinomiale * F);
FileBinomiale * Construction (Clef128 ** clefs, int debut, int fin);
FileBinomiale * SupprMin(FileBinomiale * F);
FileBinomiale * UFret(FileBinomiale * F1, FileBinomiale * F2, TournoiBinomial * T);
FileBinomiale * Union (FileBinomiale * F1, FileBinomiale * F2);
void affichageTournoiBinomial(TournoiBinomial * T);
void affichageFileBinomiale(FileBinomiale * F);
void deleteTournoiBinomial(TournoiBinomial * T);
void deleteElementFile(ElementFile * E);
void deleteFileBinomiale(FileBinomiale * F);

#endif