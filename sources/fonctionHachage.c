#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../headers/clef128.h"

unsigned int MD5(char* chaine)
{
    int r[64], k[64];
    
    //Definir r
    int valeur[4];
    valeur[0] = 7;
    valeur[1] = 12;
    valeur[2] = 17;
    valeur[3] = 22;
    for(int i = 0; i<4; i++)
    {
        r[i] = valeur[i];
        r[i+4] = valeur[i];
        r[i+8] = valeur[i];
        r[i+12] = valeur[i];
    }
    valeur[0] = 5;
    valeur[1] = 9;
    valeur[2] = 14;
    valeur[3] = 20;
    for(int i = 0; i<4; i++)
    {
        r[i+16] = valeur[i];
        r[i+20] = valeur[i];
        r[i+24] = valeur[i];
        r[i+28] = valeur[i];
    }
    valeur[0] = 4;
    valeur[1] = 11;
    valeur[2] = 16;
    valeur[3] = 23;
    for(int i = 0; i<4; i++)
    {
        r[i+32] = valeur[i];
        r[i+36] = valeur[i];
        r[i+40] = valeur[i];
        r[i+44] = valeur[i];
    }
    valeur[0] = 6;
    valeur[1] = 10;
    valeur[2] = 15;
    valeur[3] = 21;
    for(int i = 0; i<4; i++)
    {
        r[i+48] = valeur[i];
        r[i+52] = valeur[i];
        r[i+56] = valeur[i];
        r[i+60] = valeur[i];
    }

    //MD5 utilise des sinus d'entiers pour ses constantes :
    for(int i = 0; i<64; i++)
    {
        k[i] = floor(abs(sin(i+1))*pow(2,32));
    }

    //Preparation des variables
    Clef128* clef = hexaToUnsigned("0x1032547698BADCFEEFCDAB8967452301");
    
    //Preparation du message(padding) :
    int lenInit = strlen(chaine);
    strcat(chaine, "1");
    int len = strlen(chaine);
    while(len%512 != 448)
    {
        strcat(chaine, "0");
        len++;
    }
    strcpy(chaine, lenInit);

}