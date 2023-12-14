#ifndef LISTE_CHAINE_H
#define LISTE_CHAINE_H
#include "../headers/clef128.h"

typedef struct listeChainee ListeChainee;
struct listeChainee{
    Clef128* clef;
    struct listeChainee* suiv;
};

ListeChainee* findMap(ListeChainee* map, char* key);
ListeChainee* insertMap(ListeChainee* map, Clef128* clef);
int sizeMap(ListeChainee* map);
void afficheMap(ListeChainee* map);
void deleteMap(ListeChainee* map);

#endif