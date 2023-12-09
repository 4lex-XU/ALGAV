#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define F(B, C, D) ((B & C) | (~B & D))
#define G(B, C, D) ((B & D) | (C & ~D))
#define H(B, C, D) (B ^ C ^ D)
#define I(B, C, D) (C ^ (B | ~D))

unsigned int inverse(unsigned int nb)
{
    return (nb >> 24) | ((nb & 0x00FF0000) >> 8) | ((nb & 0x0000FF00) << 8) | (nb << 24);
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
    int nbZero = (56-(len+8))%64;
    int offset = (nbZero > 0) ? nbZero : 64+nbZero; //nombre de 0 à ajouter 
    int lenFinal = lenInit+offset+4; //taille du message après preparation
    unsigned char* msg = (unsigned char*)malloc(sizeof(unsigned char)*lenFinal);
    memset(msg, 0, lenFinal);
    memcpy(msg, chaine, lenInit);
    msg[len] = 1;
    //strcat(msg, "1");
    for(int i = len+1; i<offset; i++)
    {
        //strcat(msg, "0");
        msg[i] = 0;
    }
    char* bin = decToBinary(lenInit);
    //strcat(msg, bin);

    int indice = len + 1 + offset;
    memcpy(msg+indice, &bin, 64);
    printf("MSG = %s\n", msg);
    
    //Decoupage en blocs de 512 bits
    int bit = 0;
    int bloc = lenFinal/64;
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
                f = I(b,c,d);
                g = (7*i)%16;
            }
    
            unsigned int temp = d;
            d = c;
            c = b;
            b = b + leftrotate((a+f+k[i]+w[g]), r[i]);
            a = temp;
        
            printf("a = %d\n", a);
            printf("b = %d\n", b);
            printf("c = %d\n", c);
            printf("d = %d\n", d);
            printf("-------------------\n");
            
            printf("i = %d\n", i);
            printf("g = %d\n", g);
            printf("f = %d\n", f);
        }
        //fin pour
        //ajouter le resultat au bloc précédent : 
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
    }
    //fin pour
    free(msg);

    unsigned int* h = (unsigned int*)malloc(sizeof(unsigned int) * 4);
    h[0] = inverse(h0);
    h[1] = inverse(h1);
    h[2] = inverse(h2);
    h[3] = inverse(h3);
    return h;
}
int main(){

    unsigned int* md5 = MD5("Et l’unique cordeau des trompettes marines");
    printf("MD5 = %02x %02x %02x %02x\n", md5[0], md5[1], md5[2], md5[3]);

    free(md5);
    
    return 0;
}