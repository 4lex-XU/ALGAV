#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/clef128.h"
#include <time.h>

#define MAX 1000
#define NB_CLEF 1000

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("Error: file missing\n");
    }

    FILE* file = NULL;
    if((file = fopen(argv[1], "r")) == NULL)
    {
        printf("Error: not open\n");
    }

    Clef128* clefs[NB_CLEF];
    char buffer[MAX];
    int i = 0;
    while(fgets(buffer, MAX, file) != NULL)
    {
        Clef128* clef = hexaToUnsigned(buffer);
        clefs[i] = clef;
        i++;
    }

    srand(time(NULL));
    int k1, k2;
    do{
        k1 = rand()%NB_CLEF+1;
        k2 = rand()%NB_CLEF+1;
    }while(k1 == k2);

    if(inf(clefs[k1], clefs[k2]) == 1)
    {
        printf("La clé2 : %u %u %u %u est strictement superieur à la clé1 : %u %u %u %u \n",
        clefs[k2]->b32_4, clefs[k2]->b32_3, clefs[k2]->b32_2, clefs[k2]->b32_1,
        clefs[k1]->b32_4, clefs[k1]->b32_3, clefs[k1]->b32_2, clefs[k1]->b32_1);
    }
    else{
        printf("La clé1 : %u %u %u %u est superieur ou egal à la clé2 : %u %u %u %u \n",
        clefs[k1]->b32_4, clefs[k1]->b32_3, clefs[k1]->b32_2, clefs[k1]->b32_1,
        clefs[k2]->b32_4, clefs[k2]->b32_3, clefs[k2]->b32_2, clefs[k2]->b32_1);
    }

    if(eg(clefs[k1], clefs[k2]) == 1)
    {
        printf("Les 2 clefs sont égaux\n");
    }
    else{
        printf("Les 2 clefs ne sont pas égaux\n");
    }

    fclose(file);

    return 0;
}