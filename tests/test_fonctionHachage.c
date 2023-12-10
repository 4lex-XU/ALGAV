#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../headers/fonctionHachage.h"

int main(){

    unsigned int* md5 = MD5("Et l’unique cordeau des trompettes marines");
    printf("MD5 = %08x %08x %08x %08x\n", md5[0], md5[1], md5[2], md5[3]);
    free(md5);

    unsigned int* md52 = MD5("Et l’unique cordeau des trompettes marinEs");
    printf("MD5 = %08x %08x %08x %08x\n", md52[0], md52[1], md52[2], md52[3]);
    free(md52);

    unsigned int* md53 = MD5("exultation");
    printf("MD5 = %08x %08x %08x %08x\n", md53[0], md53[1], md53[2], md53[3]);
    free(md53);

    unsigned int* md54 = MD5("directing");
    printf("MD5 = %08x %08x %08x %08x\n", md54[0], md54[1], md54[2], md54[3]);
    free(md54);
    
    return 0;
}