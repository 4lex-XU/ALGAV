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
    char* ma_clef = (char*)malloc(sizeof(char)*(strlen(clef)-4));
    strncpy(ma_clef, clef+2, (strlen(clef)-4));
    Clef128* res = (Clef128*)malloc(sizeof(Clef128));
    char* octet4 = (char*)malloc(sizeof(char)*8);
loop:   
    if(strlen(ma_clef) == 32)
    {  
        int j = 0;
        for(int i = 0; i<strlen(ma_clef); i++)
        {
            octet4[j] = ma_clef[i];
            j++;
            switch(i){
            case 7:
                res->b32_4 = strtoul(octet4, NULL, 16);
                j = 0;
                break;
            case 15:
                res->b32_3 = strtoul(octet4, NULL, 16);
                j = 0;
                break;
            case 23:
                res->b32_2 = strtoul(octet4, NULL, 16);
                j = 0;
                break;   
            }
        }
        res->b32_1 = strtoul(octet4, NULL, 16);
    }
    else{
        char* newclef;
        memset(newclef, '0', (32-strlen(ma_clef))*sizeof(char));
        strcat(newclef, ma_clef);
        strncpy(ma_clef, newclef, 32);
        goto loop;

    }

    free(ma_clef);
    free(octet4);
    return res;
}