#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../headers/clef128.h"

#define F(B, C, D) ((B & C) | (~B & D))
#define G(B, C, D) ((B & D) | (C & ~D))
#define H(B, C, D) (B ^ C ^ D)
#define I(B, C, D) (C ^ (B | ~D))

char* decToBinary(int nb)
{
    char tab[64];
    memset(tab, '0', 64);
    for(int i = 0; nb>0; i++)
    {
        tab[i] = nb%2;
        nb = nb/2;
    }
    return tab;
}

unsigned int leftrotate(unsigned int nb, unsigned int decalage)
{
    return nb << decalage | nb >> (32-decalage);
}


unsigned int MD5(char* chaine)
{
    int r[64], k[64];
    
    //Definir r
    r[] =  {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
            5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
            4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
            6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    //MD5 utilise des sinus d'entiers pour ses constantes :
    for(int i = 0; i<64; i++)
    {
        k[i] = floor(abs(sin(i+1))*pow(2,32));
    }

    //Preparation des variables
    //Clef128* clef = hexaToUnsigned("0x1032547698BADCFEEFCDAB8967452301");
    unsigned int h0 = 0x67452301;
    unsigned int h1 = 0xEFCDAB89;
    unsigned int h2 = 0x98BADCFE;
    unsigned int h3 = 0x10325476;

    //Preparation du message(padding) :
    int lenInit = strlen(chaine);
    int len = lenInit*8; //longueur de la chaine en nombre de bits 
    int zero = (448-(len+1))%512;
    int offset = (zero > 0) ? zero : 512-zero; //nombre de 0 à ajouter 
    char* msg = (char*)malloc(sizeof(char)*len+1+offset+64);
    memcpy(msg, chaine, lenInit);
    strcat(msg, "1");
    for(int i = 0; i<offset; i++)
    {
        strcat(msg, "0");
    }
    char* bin = decToBinary(len);
    strcpy(msg, bin);

    //Decoupage en blocs de 512 bits
    int bit = 0;
    int bloc = (len+1+offset+64)/512;
    for(int b = 0; b<bloc; b++)
    {
        unsigned int w[16]; //16 mots de 32 bits
        for(int j = 0; j<16; j++)
        {
            memcpy(w[j],msg+bit, 32);
            bit += 32;
        }

        unsigned int a = h0;
        unsigned int b = h1;
        unsigned int c = h2;
        unsigned int d = h3;

        for(int i = 0; i<63; i++)
        {
            int f,g;
            if(i >= 0 && i <= 15)
            {
                int f = F(b,c,d);
                int g = i;
            }else{
                if(i >= 16 && i <= 31)
                {
                    f = F(d,b,c);
                    g = (3*i + 5)%16;
                }else{
                    if(i >= 32 && i <= 47)
                    {
                        f = H(b,c,d);
                        g = (3*i + 5)%16;
                    }else{
                        if(i >= 48 && i <= 63)
                        {
                            f = I(c,b,d);
                            g = (7*i)%16;
                        }
                    }
                }
            }
            //fin pour
            int temp = d;
            d = c;
            c = b;
            b = leftrotate((a+f+k[i]+w[g]), r[i]) + b;
            a = temp;
        }
        //fin pour
        //ajouter le resultat au bloc précédent : 
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
    }
    //fin pour
    char* res = (char*)malloc(sizeof(char)*32);
    memcpy(res, h0, 8);
    memcpy(res, h1, 8);
    memcpy(res, h2, 8);
    memcpy(res, h3, 8);
    return res;
}