#include "clef128.h"
#ifndef H_TASARBRE
#define H_TASARBRE
#include "../headers/listeChaine.h"

typedef struct tasArbre TasArbre;
struct tasArbre {
    Clef128* clef;
    struct tasArbre * fg;
    struct tasArbre * fd;
    struct tasArbre * parent; // parent du noeud
    int hauteur; // hauteur de l'arbre
    int noeud; // nombre de noeud present dans l'arbre
};

typedef struct Element Element;
struct Element {
    TasArbre* noeud;
    struct Element* suiv;
    struct Element* pre;
};

typedef struct Liste Liste;
struct Liste
{
    Element* tete;
    Element* queue;
};

TasArbre* initialisation();
Clef128* copy(Clef128* clef);
TasArbre* creerNoeud(Clef128* clef);
void echangeClef(Clef128* a, Clef128* b);
void echangeRacine(TasArbre* tas);
void reequilibrageRemontee(TasArbre* tas);
void reequilibrageDescente(Element* tete, int len);
void majHauteurAjout(TasArbre* tas);
void majNoeudAjout(TasArbre* tas);
void majHauteurSuppr(TasArbre* tas);
void majNoeudSuppr(TasArbre* tas);
void ajoutTasArbre (TasArbre * tas, Clef128* clef);
TasArbre* ajoutsIteratifsTasArbre (Clef128* clefs[], int len);
Clef128 supprMinTasArbre (TasArbre* tas, TasArbre* racine);
Element* ajoutListe(TasArbre* noeud);
void deleteElement(Element* tete);
TasArbre* constructionTasArbre(Clef128* clefs[], int len);
//void UnionParcours(ListeChainee** liste, TasArbre* tas);
TasArbre* UnionTasArbre(TasArbre* tas1, TasArbre* tas2);
void affichageTasArbre(TasArbre* tas);
void deleteTasArbre(TasArbre* tas);

#endif