#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/clef128.h"
#include "../headers/tasTableau.h"
#include "../headers/tasArbre.h"
#include "../headers/fileBinomiale.h"
#include "../headers/listeChaine.h"
#include "../headers/fonctionHachage.h"
#include <time.h>
#include <math.h>

#define MAX 1000

double mesurerTempsConstructionTableau(Clef128 **clefs, int deb, int fi) {
    clock_t debut, fin;
    debut = clock();
    TasTableau * t = constructionTasTableau(clefs, deb, fi);
    fin = clock();
    deleteTasTableau(t);
    return (double)(fin - debut) / CLOCKS_PER_SEC;
}

double mesurerTempsConstructionTasArbre(Clef128 **clefs, int len)
{
    clock_t debut, fin;
    debut = clock();
    TasArbre* t = constructionTasArbre(clefs, len);
    fin = clock();
    deleteTasArbre(t);
    return (double)(fin - debut) / CLOCKS_PER_SEC;
}

double mesurerTempsConstructionFile(Clef128 **clefs, int deb, int fi) {
    clock_t debut, fin;
    debut = clock();
    FileBinomiale * F = Construction(clefs, deb, fi);
    fin = clock();
    deleteFileBinomiale(F);
    return (double)(fin - debut) / CLOCKS_PER_SEC;
}

int main()
{
    FILE * file = NULL;
    FILE * fichier = NULL;
    if ((fichier = fopen("./resultats/resultats_temps_6_16_Construction.txt", "w")) == NULL) {
        printf("Error: not open\n");
        return 0;
    }

    char * jeux[37] = 
    {   "./Shakespeare/1henryiv.txt",
        "./Shakespeare/1henryvi.txt",
        "./Shakespeare/2henryiv.txt",
        "./Shakespeare/2henryvi.txt",
        "./Shakespeare/3henryvi.txt",
        "./Shakespeare/allswell.txt",
        "./Shakespeare/asyoulikeit.txt",
        "./Shakespeare/cleopatra.txt",
        "./Shakespeare/comedy_errors.txt",
        "./Shakespeare/coriolanus.txt",
        "./Shakespeare/cymbeline.txt",
        "./Shakespeare/hamlet.txt",
        "./Shakespeare/henryv.txt",
        "./Shakespeare/henryviii.txt",
        "./Shakespeare/john.txt",
        "./Shakespeare/julius_caesar.txt",
        "./Shakespeare/lear.txt",
        "./Shakespeare/lll.txt",
        "./Shakespeare/macbeth.txt",
        "./Shakespeare/measure.txt",
        "./Shakespeare/merchant.txt",
        "./Shakespeare/merry_wives.txt",
        "./Shakespeare/midsummer.txt",
        "./Shakespeare/much_ado.txt",
        "./Shakespeare/othello.txt",
        "./Shakespeare/pericles.txt",
        "./Shakespeare/richardii.txt",
        "./Shakespeare/richardiii.txt",
        "./Shakespeare/romeo_juliet.txt",
        "./Shakespeare/taming_shrew.txt",
        "./Shakespeare/tempest.txt",
        "./Shakespeare/timon.txt",
        "./Shakespeare/titus.txt",
        "./Shakespeare/troilus_cressida.txt",
        "./Shakespeare/twelfth_night.txt",
        "./Shakespeare/two_gentlemen.txt",
        "./Shakespeare/winters_tale.txt",
    };

    char buffer[MAX];
    ListeChainee* map = NULL;
    ListeChainee* tmp = NULL;

    // LECTURE DES FICHIERS
    for(int i = 0; i<37; i++)
    {   
        if((file = fopen(jeux[i], "r")) == NULL)
        {
            printf("Error: not open\n");
            return 0;
        }

        // LECTURE DES CLES DANS LE FICHIER
        while(fgets(buffer, MAX, file) != NULL)
        {
            // LISTE DES MOTS DU DOSSIER 
            if((tmp = findMap(map, buffer)) == NULL)
            {
                unsigned int* md5 = MD5(buffer);
                Clef128* clef = (Clef128*)malloc(sizeof(Clef128));
                clef->clef_hexa = (char*)malloc(sizeof(char)*32);
                clef->b32_1 = md5[3];
                clef->b32_2 = md5[2];
                clef->b32_3 = md5[1];
                clef->b32_4 = md5[0];
                strcpy(clef->clef_hexa, buffer);
                map = insertMap(map, clef);
            }
        }
        fclose(file);
    }

    int SIZEMAP = sizeMap(map);
    printf("sizeMap = %d\n", SIZEMAP);

    double tempsMoyenConstructionTableau = 0;
    double tempsMoyenConstructionArbre = 0;
    double tempsMoyenConstructionFile = 0;

    Clef128* clefs[SIZEMAP];
    int i = 0;
    tmp = map;
    // CREATION DU TABLEAU DE CLEFS
    while(tmp != NULL)
    {
        clefs[i] = tmp->clef;
        i++;
        tmp = tmp->suiv;
    }

    tempsMoyenConstructionTableau = mesurerTempsConstructionTableau(clefs, 0, SIZEMAP);
    tempsMoyenConstructionArbre = mesurerTempsConstructionTasArbre(clefs, SIZEMAP);
    tempsMoyenConstructionFile = mesurerTempsConstructionFile(clefs, 0, SIZEMAP);

    fprintf(fichier, "Taille: %d, TasTableau: %f, TasArbre: %f, FileBinomiale: %f\n", SIZEMAP, tempsMoyenConstructionTableau, tempsMoyenConstructionArbre, tempsMoyenConstructionFile);

    deleteMap(map);
    fclose(fichier);

    return 0;
}