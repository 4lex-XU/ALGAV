#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/clef128.h"
#include "../headers/arbreRecherche.h"
#include <time.h>
#include <math.h>

#define MAX 1000

double mesurerTempsAjoutsIteratifs(Clef128 **clefs, int len)
{
    clock_t debut, fin;
    debut = clock();
    ajoutsIteratifsArbreRecherche(clefs, len);
    fin = clock();
    return (double)(fin - debut) / CLOCKS_PER_SEC;
}

int main(){

    FILE * file = NULL;
    FILE * fichier = NULL;
    if ((fichier = fopen("./resultats/resultats_temps_ArbreRecherche.txt", "w")) == NULL) {
        printf("Error: not open\n");
        return 0;
    }

    // TESTS DE TEMPS
    int tailles[] = {1000, 5000, 10000, 20000, 50000, 80000, 120000, 200000};
    int nbTailles = sizeof(tailles) / sizeof(tailles[0]);
    char * jeux[40] = 
    {   "./cles_alea/jeu_1_nb_cles_1000.txt",
        "./cles_alea/jeu_2_nb_cles_1000.txt",
        "./cles_alea/jeu_3_nb_cles_1000.txt",
        "./cles_alea/jeu_4_nb_cles_1000.txt",
        "./cles_alea/jeu_5_nb_cles_1000.txt",

        "./cles_alea/jeu_1_nb_cles_5000.txt",
        "./cles_alea/jeu_2_nb_cles_5000.txt",
        "./cles_alea/jeu_3_nb_cles_5000.txt",
        "./cles_alea/jeu_4_nb_cles_5000.txt",
        "./cles_alea/jeu_5_nb_cles_5000.txt",

        "./cles_alea/jeu_1_nb_cles_10000.txt",
        "./cles_alea/jeu_2_nb_cles_10000.txt",
        "./cles_alea/jeu_3_nb_cles_10000.txt",
        "./cles_alea/jeu_4_nb_cles_10000.txt",
        "./cles_alea/jeu_5_nb_cles_10000.txt",

        "./cles_alea/jeu_1_nb_cles_20000.txt",
        "./cles_alea/jeu_2_nb_cles_20000.txt",
        "./cles_alea/jeu_3_nb_cles_20000.txt",
        "./cles_alea/jeu_4_nb_cles_20000.txt",
        "./cles_alea/jeu_5_nb_cles_20000.txt",

        "./cles_alea/jeu_1_nb_cles_50000.txt",
        "./cles_alea/jeu_2_nb_cles_50000.txt",
        "./cles_alea/jeu_3_nb_cles_50000.txt",
        "./cles_alea/jeu_4_nb_cles_50000.txt",
        "./cles_alea/jeu_5_nb_cles_50000.txt",

        "./cles_alea/jeu_1_nb_cles_80000.txt",
        "./cles_alea/jeu_2_nb_cles_80000.txt",
        "./cles_alea/jeu_3_nb_cles_80000.txt",
        "./cles_alea/jeu_4_nb_cles_80000.txt",
        "./cles_alea/jeu_5_nb_cles_80000.txt",

        "./cles_alea/jeu_1_nb_cles_120000.txt",
        "./cles_alea/jeu_2_nb_cles_120000.txt",
        "./cles_alea/jeu_3_nb_cles_120000.txt",
        "./cles_alea/jeu_4_nb_cles_120000.txt",
        "./cles_alea/jeu_5_nb_cles_120000.txt",

        "./cles_alea/jeu_1_nb_cles_200000.txt",
        "./cles_alea/jeu_2_nb_cles_200000.txt",
        "./cles_alea/jeu_3_nb_cles_200000.txt",
        "./cles_alea/jeu_4_nb_cles_200000.txt",
        "./cles_alea/jeu_5_nb_cles_200000.txt"
    };

    double tempsMoyenAjoutsIteratifs = 0;

    for (int i = 0; i < nbTailles*5; i++) {
        int taille = tailles[i/5];
        // OUVERTURE
        //printf("%s\n", jeux[i]);
        if((file = fopen(jeux[i], "r")) == NULL)
        {
            printf("Error: not open\n");
            return 0;
        }
        
        Clef128* clefs[taille];
        char buffer[MAX];
        int j = 0;

        // LECTURE DES CLES DANS LE FICHIER
        while(fgets(buffer, MAX, file) != NULL)
        {
            //printf("%s\n", buffer);
            Clef128* clef = hexaToUnsigned(buffer);
            clefs[j] = clef;
            j++;
        }
    
        tempsMoyenAjoutsIteratifs += mesurerTempsAjoutsIteratifs(clefs, taille);
       
        if((i+1)%5 == 0){
            tempsMoyenAjoutsIteratifs /= 5;
            fprintf(fichier, "Taille: %d, ajoutsIteratifs: %f\n", taille, tempsMoyenAjoutsIteratifs);   
            tempsMoyenAjoutsIteratifs = 0;
        }
        // Libérer la mémoire
        deleteClefs(clefs, taille);
        fclose(file);
    }
    fclose(fichier);
}