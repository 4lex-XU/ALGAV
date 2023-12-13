#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../headers/arbreRecherche.h"
#include "../headers/clef128.h"

int main () {
    Noeud* racine = NULL;
    Clef128* clef = hexaToUnsigned("0x00000000000000000000000000000000");
    racine = inserer(racine, clef);
    clef = hexaToUnsigned("0x00000000000000000000000000000001");
    racine = inserer(racine, clef);
    clef = hexaToUnsigned("0x00000000000000000000000000000002");
    racine = inserer(racine, clef);
    clef = hexaToUnsigned("0x00000000000000000000000000003");
    racine = inserer(racine, clef);

    printf("%d\n", rechercher(racine, hexaToUnsigned("0x00000000000000000000000000000000")));
    
    return 0;
}