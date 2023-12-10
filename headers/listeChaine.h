#ifndef LISTE_CHAINE_H
#define LISTE_CHAINE_H

typedef struct HashMap HashMap;
struct HashMap{
    char* key;
    HashMap* suiv;
};

HashMap* findMap(HashMap* map, char* key);
HashMap* insertMap(HashMap* map, char* key);
int sizeMap(HashMap* map);
void afficheMap(HashMap* map);
void deleteMap(HashMap* map);

#endif