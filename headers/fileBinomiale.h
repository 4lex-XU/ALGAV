#include "clef128.h"
#ifndef H_FILEBINOMIALE
#define H_FILEBINOMIALE

typedef struct tournoiBinomiale
{
    Clef128 clef;
    struct tournoiBinomiale * pere;
    struct tournoiBinomiale * fils;
    struct tournoiBinomiale * frere; // frere droit
} TournoiBinomiale;


typedef struct fileBinomiale 
{
    TournoiBinomiale * tournois;
} FileBinomiale;


FileBinomiale * supprMin (FileBinomiale * F);
FileBinomiale * ajout (FileBinomiale * F, TournoiBinomiale * T);
FileBinomiale * construction (Clef128* clefs[], int deb, int fin);
FileBinomiale * Union(FileBinomiale * F1, FileBinomiale * F2);
void affichageFileBinomiale(FileBinomiale * F);
void deleteFile(FileBinomiale * F);

#endif