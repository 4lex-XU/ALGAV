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

double mesurerTempsSuppTableau(TasTableau* t, int nb) {
    clock_t debut, fin;
    debut = clock();
    for(int i = 0; i<nb; i++)
    {
        supprMinTasTableau(t);
    }
    fin = clock();
    return (double)(fin - debut) / CLOCKS_PER_SEC;
}

double mesurerTempsSuppTasArbre(TasArbre* t, int nb)
{
    clock_t debut, fin;
    debut = clock();
    for(int i = 0; i<nb; i++)
    {
        supprMinTasArbre(t,t);
    }
    fin = clock();
    return (double)(fin - debut) / CLOCKS_PER_SEC;
}

double mesurerTempsSuppFile(FileBinomiale* F, int nb) 
{
    clock_t debut, fin;
    debut = clock();
    for(int i = 0; i < nb; i++)
    {
        F = SupprMin(F);
    }
    fin = clock();
    return (double)(fin - debut) / CLOCKS_PER_SEC;
}

int main()
{
    FILE * file = NULL;
    FILE * fichier = NULL;
    if ((fichier = fopen("./resultats/resultats_temps_6_16_Suppression.txt", "w")) == NULL) {
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
    //printf("sizeMap = %d\n", SIZEMAP); // 23086

    double tempsMoyenSuppTableau = 0;
    double tempsMoyenSuppArbre = 0;
    double tempsMoyenSuppFile = 0;

    Clef128* clefs[SIZEMAP];
    int i = 0;
    tmp = map;
    while(tmp != NULL)
    {
        clefs[i] = tmp->clef;
        i++;
        tmp = tmp->suiv;
    }

    for(int i = 1; i<20; i++)
    {
        TasTableau* t1 = constructionTasTableau(clefs, 0, SIZEMAP);
        TasArbre* t2 = constructionTasArbre(clefs, SIZEMAP);
        FileBinomiale* f1 = Construction(clefs, 0, SIZEMAP);

        tempsMoyenSuppTableau += mesurerTempsSuppTableau(t1, i);
        tempsMoyenSuppArbre += mesurerTempsSuppTasArbre(t2, i);
        tempsMoyenSuppFile += mesurerTempsSuppFile(f1, i);
        //printf("i = %d\n", i);
        deleteTasTableau(t1);
        deleteTasArbre(t2);
        //deleteFileBinomiale(f1);

        fprintf(fichier, "Nombre_de_clefs: %d, TasTableau: %f, TasArbre: %f, FileBinomiale: %f\n", i, tempsMoyenSuppTableau, tempsMoyenSuppArbre, tempsMoyenSuppFile);
    }

    deleteMap(map);
    fclose(fichier);

    return 0;
}