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
    char* octet4;
    char* clef_rev = strrev(clef+2);
    printf("reverse = %s \n", clef_rev);
    Clef128* res = (Clef128*)malloc(sizeof(Clef128));
    for(int i = 0; i<strlen(clef_rev); i++)
    {
        octet4 = strcat(octet4, clef_rev[i]);
        switch(i){
            case 8:
                res->b32_1 = strtoul(octet4, NULL, 16);
                octet4 = "";
                break;
            case 16:
                res->b32_2 = strtoul(octet4, NULL, 16);
                octet4 = "";
                break;
            case 24:
                res->b32_3 = strtoul(octet4, NULL, 16);
                octet4 = "";
                break;   
        }   
    }
    res->b32_4 = strtoul(octet4, NULL, 16);
    return res;
}