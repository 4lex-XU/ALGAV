#include <stdio.h>
#include <stdlib.h>
#include "../headers/clef128.h"
#include <string.h>

int inf(Clef128* clef1, Clef128* clef2)
{
    if (clef1->b32_4 < clef2->b32_4) return 1;
    if (clef1->b32_4 > clef2->b32_4) return 0;
    if (clef1->b32_3 < clef2->b32_3) return 1;
    if (clef1->b32_3 > clef2->b32_3) return 0;
    if (clef1->b32_2 < clef2->b32_2) return 1;
    if (clef1->b32_2 > clef2->b32_2) return 0;
    if (clef1->b32_1 < clef2->b32_1) return 1;
    return 0;
}

int eg(Clef128* clef1, Clef128* clef2)
{
    if (clef1->b32_4 != clef2->b32_4) return 0;
    if (clef1->b32_3 != clef2->b32_3) return 0;
    if (clef1->b32_2 != clef2->b32_2) return 0;
    if (clef1->b32_1 != clef2->b32_1) return 0;
    return 1;
}

Clef128* hexaToUnsigned(char* clef)
{
    int len = strlen(clef)-4;
    
    // RECOPIE CLE SANS 0x
    char* ma_clef = (char*)malloc(sizeof(char)*32);
    strncpy(ma_clef, clef+2, 32);

    // ALLOCATION CLEF
    Clef128* res = (Clef128*)malloc(sizeof(Clef128));
    res->clef_hexa = (char*)malloc(sizeof(char)*33);
    res->clef_hexa[32] = '\0';

    // TAMPON POUR LE STOCKAGE DES UNSIGNED INT
    char* octet4 = (char*)malloc(sizeof(char)*9);
    octet4[8] = '\0';

    // SI CLE 16 OCTETS
    if(len == 32)
    {  
        strncpy(res->clef_hexa, ma_clef, 32);
        res->b32_4 = strtoul(strncpy(octet4, ma_clef, 8), NULL, 16);
        res->b32_3 = strtoul(strncpy(octet4, ma_clef+8, 8), NULL, 16);
        res->b32_2 = strtoul(strncpy(octet4, ma_clef+16, 8), NULL, 16);
        res->b32_1 = strtoul(strncpy(octet4, ma_clef+24, 8), NULL, 16);
    }
    else{
        // AJOUT ZERO DEBUT DE CHAINE
        int nbZero = (32-len);
        char *newclef = (char*)malloc(sizeof(char)*32);
        memset(newclef, '0', (32-len)*sizeof(char));
        strncpy(newclef+nbZero, ma_clef,32-nbZero);

        strncpy(res->clef_hexa, newclef, 32);
        // TRAITEMENT AVEC LA NOUVELLE CHAINE CREE
        res->b32_4 = strtoul(strncpy(octet4, newclef, 8), NULL, 16);
        res->b32_3 = strtoul(strncpy(octet4, newclef+8, 8), NULL, 16);
        res->b32_2 = strtoul(strncpy(octet4, newclef+16, 8), NULL, 16);
        res->b32_1 = strtoul(strncpy(octet4, newclef+24, 8), NULL, 16);

        free(newclef);
    }

    free(ma_clef);
    free(octet4);
    return res;
}

void affichageClef(Clef128* clef)
{
    printf("Clef = %s -> %u %u %u %u\n", 
    clef->clef_hexa, clef->b32_4, clef->b32_3, clef->b32_2, clef->b32_1);
}

void deleteClefs(Clef128 **clefs, int taille) {
    if (clefs != NULL) {
        for (int i = 0; i < taille; i++) {
            if (clefs[i] != NULL) {
                // Libérer d'autres ressources allouées dans Clef128 si nécessaire
                free(clefs[i]);
            }
        }
        free(clefs);
    }
}