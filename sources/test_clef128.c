#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/clef128.h"

#define MAX 1000

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

    Clef128 clefs[1000];
    char buffer[MAX];
    while(fgets(buffer, MAX, file) != NULL)
    {
        printf("%s\n", buffer);
        Clef128* clef = hexaToUnsigned(buffer);
        printf("%d\n", clef->b32_1);
    }

    fclose(file);

    return 0;
}