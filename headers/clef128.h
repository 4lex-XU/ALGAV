#ifndef H_CLEF
#define H_CLEF

typedef struct clef128 Clef128;
struct clef128{
    unsigned int b32_1; //poids faibles
    unsigned int b32_2;
    unsigned int b32_3;
    unsigned int b32_4; //poids forts
    char* clef_hexa; // cles en hexa
};

int inf(Clef128* clef1, Clef128* clef2);
int eg(Clef128* clef1, Clef128* clef2);
Clef128* hexaToUnsigned(char* clef);
void affichageClef(Clef128* clef);

#endif