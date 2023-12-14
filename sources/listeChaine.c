#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../headers/listeChaine.h"
#include "../headers/clef128.h"

ListeChainee* findMap(ListeChainee* map, char* key)
{
    while(map != NULL)
    {
        if(strcmp(map->clef->clef_hexa, key) == 0)
        {
            return map;
        }
        map = map->suiv;
    }
    
    return NULL;
}

ListeChainee* insertMap(ListeChainee* map, Clef128* clef)
{
    ListeChainee* tmp = (ListeChainee*)malloc(sizeof(ListeChainee));
    tmp->clef = clef;
    tmp->suiv = NULL;
    if(map == NULL)
    {
        map = tmp;
        return map;
    }
    ListeChainee* map2 = map;
    while(map2->suiv != NULL)
    {
        map2 = map2->suiv;
    }
    map2->suiv = tmp;
    return map;
}

int sizeMap(ListeChainee* map)
{
    int len = 0;
    ListeChainee* tmp = map;
    while(tmp != NULL)
    {
        len++;
        tmp = tmp->suiv;
    }
    return len;
}

void afficheMap(ListeChainee* map){
    if(map == NULL)
    {   
        return;
    }
    affichageClef(map->clef);
    afficheMap(map->suiv);
}

void deleteMap(ListeChainee* map)
{
    while(map != NULL)
    {
        ListeChainee* suiv = map->suiv;
        free(map->clef->clef_hexa);
        free(map->clef);
        free(map);
        map = suiv;
    }
}