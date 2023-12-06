#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define F(B, C, D) ((B & C) | (~B & D))
#define G(B, C, D) ((B & D) | (C & ~D))
#define H(B, C, D) (B ^ C ^ D)
#define I(B, C, D) (C ^ (B | ~D))

char* decToBinary(int nb)
{
    char* tab = (char*)malloc(sizeof(char)*65);
    tab[64] = '\0';
    memset(tab, '0', 64);
    int index = 0;
    while (nb > 0 && index >= 0)
    {
        tab[index] = (nb % 2) + '0';
        nb = nb / 2;
        index++;
    }
    return tab;
}

unsigned int leftrotate(unsigned int nb, unsigned int decalage)
{
    return nb << decalage | nb >> (32-decalage);
}


unsigned int* MD5(char* chaine)
{   
    //Definir r
    int r[] =  {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                5,  9, 14, 20, 5,  9, 14, 20, 5, 9, 14, 20, 5,  9, 14, 20,
                4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    //MD5 utilise des sinus d'entiers pour ses constantes :
    unsigned int k[64];
    for(int i = 0; i<64; i++)
    {
        k[i] = floor(fabs(sin(i+1))*pow(2,32));
    }

    //Preparation des variables
    unsigned int h0 = 0x67452301;
    unsigned int h1 = 0xEFCDAB89;
    unsigned int h2 = 0x98BADCFE;
    unsigned int h3 = 0x10325476;

    //Preparation du message(padding) :
    int lenInit = strlen(chaine);
    int len = lenInit*8;
    int nbZero = (448-(len+1))%512;
    int offset = (nbZero > 0) ? nbZero : 512-nbZero; //nombre de 0 à ajouter 
    int lenFinal = len+1+offset+64; //taille du message après preparation
    unsigned char* msg = (unsigned char*)malloc(sizeof(unsigned char)*lenFinal+1);
    msg[lenFinal] = '\0';

    memcpy(msg, chaine, lenInit);
    msg[lenInit] = (unsigned char)0x80;
    for(int i = lenInit+1; i<offset; i++)
    {
        msg[i] = 0;
    }
    char* bin = decToBinary(lenInit);
    int indice = lenInit + 1 + offset;
    memcpy(msg+indice, &bin, 64);
    printf("MSG = %s\n", msg);
    
    //Decoupage en blocs de 512 bits
    int bit = 0;
    int bloc = lenFinal/512;
    unsigned int w[16]; //16 mots de 32 bits = 4o
    for(int b = 0; b<bloc; b++)
    {
        
        for(int j = 0; j<16; j++)
        {
            memcpy(&w[j],msg+bit, 4); //chaque case contient 32bits = 4o * 16 = 64o = 512bits
            bit += 4;
            printf("msg+bit = %s\n", msg+bit);
            printf("w = %d\n", w[14]);
        }

        unsigned int a = h0;
        unsigned int b = h1;
        unsigned int c = h2;
        unsigned int d = h3;
        
        for(int i = 0; i<64; i++)
        {
            unsigned int f, g;
            if(i >= 0 && i <= 15)
            {
                f = F(b,c,d);
                g = i;
            }
            if(i >= 16 && i <= 31)
            {
                f = F(d,b,c);
                g = (5*i + 1)%16;
            }
            if(i >= 32 && i <= 47)
            {
                f = H(b,c,d);
                g = (3*i + 5)%16;
            }
            if(i >= 48 && i <= 63)
            {
                f = I(c,b,d);
                g = (7*i)%16;
            }

            unsigned int temp = d;
            d = c;
            c = b;
            b = b + leftrotate((a+f+k[i]+w[g]), r[i]);
            a = temp;

            printf("w = %d\n", w[g]);

            
        }
        //fin pour
        //ajouter le resultat au bloc précédent : 
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
    }
    //fin pour
    
    //free(msg);
    //free(bin);

    unsigned int* h = (unsigned int*)malloc(sizeof(unsigned int) * 4);
    h[0] = h0;
    h[1] = h1;
    h[2] = h2;
    h[3] = h3;
    return h;
}