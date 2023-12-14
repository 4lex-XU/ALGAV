#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../headers/fonctionHachage.h"
#include "../headers/arbreRecherche.h"
#include "../headers/listeChaine.h"

#define MAX 1000
#define NBKEY 26588

int main()
{
    FILE * file = NULL;
    FILE * fichier = NULL;
    if ((fichier = fopen("./resultats/resultats_collisions.txt", "w")) == NULL) {
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
    Noeud* arbre_rech = NULL;
    // LECTURE DES FICHIERS
    for(int i = 0; i<37; i++)
    {   
        if((file = fopen(jeux[i], "r")) == NULL)
        {
            printf("Error: not open\n");
            return 0;
        }

        // LECTURE DES CLES DANS LE FICHIER + CREATION DE LA LISTE DE MOTS 
        while(fgets(buffer, MAX, file) != NULL)
        {
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

    //afficheMap(map);
    
    // Q6.14
    int SIZEMAP = sizeMap(map);
    Clef128* clefs[SIZEMAP];
    int i = 0;
    tmp = map;
    while(tmp != NULL)
    {
        clefs[i] = tmp->clef;
        arbre_rech = inserer(arbre_rech, clefs[i]);
        i++;
        tmp = tmp->suiv;
    }

    // Q6.15
    ListeChainee* collision = NULL;
    for(int i = 0; i<SIZEMAP-1; i++)
    {
        if(rechercher(arbre_rech, clefs[i]) == 0)
        {
            printf("i = %d\n", i );
            printf("----------------\n");
            collision = insertMap(collision, clefs[i]);
            fprintf(fichier,"Clef = %s -> %u %u %u %u\n", 
                            clefs[i]->clef_hexa, clefs[i]->b32_4, clefs[i]->b32_3, clefs[i]->b32_2, clefs[i]->b32_1);
        }
    }

    //afficheMap(collision);
    int SIZECOL = sizeMap(collision);
    printf("sizeCol = %d\n", SIZECOL); // 0 collision
    deleteMap(collision);
    deleteMap(map);
    fclose(fichier);

    return 0;
}