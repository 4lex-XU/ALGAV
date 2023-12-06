#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../headers/fonctionHachage.h"

int main(){

    unsigned int* md5 = MD5("Et l’unique cordeau des trompettes marines");
    printf("MD5 = %02x %02x %02x %02x\n", md5[0], md5[1], md5[2], md5[3]);

    free(md5);
    
    return 0;
}