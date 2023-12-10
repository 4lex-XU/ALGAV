#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../headers/listeChaine.h"

HashMap* findMap(HashMap* map, char* key)
{
    while(map != NULL)
    {
        if(strcmp(map->key, key) == 0)
        {
            return map;
        }
        map = map->suiv;
    }
    
    return NULL;
}

HashMap* insertMap(HashMap* map, char* key)
{
    HashMap* tmp = (HashMap*)malloc(sizeof(HashMap));
    tmp->key = (char*)malloc(sizeof(char)*32);
    strcpy(tmp->key, key);
    tmp->suiv = NULL;
    if(map == NULL)
    {
        map = tmp;
        return map;
    }
    HashMap* map2 = map;
    while(map2->suiv != NULL)
    {
        map2 = map2->suiv;
    }
    map2->suiv = tmp;
    return map;
}

int sizeMap(HashMap* map)
{
    int len = 0;
    HashMap* tmp = map;
    while(tmp != NULL)
    {
        len++;
        tmp = tmp->suiv;
    }
    return len;
}

void afficheMap(HashMap* map){
    if(map == NULL)
    {   
        return;
    }
    printf("%s\n", map->key);
    afficheMap(map->suiv);
}

void deleteMap(HashMap* map)
{
    while(map != NULL)
    {
        HashMap* suiv = map->suiv;
        free(map->key);
        free(map);
        map = suiv;
    }
}