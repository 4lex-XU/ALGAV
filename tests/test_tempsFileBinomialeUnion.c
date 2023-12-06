#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/clef128.h"
#include "../headers/fileBinomiale.h"
#include <time.h>
#include <math.h>

#define MAX 1000

double mesurerTempsUnion(FileBinomiale* F1, FileBinomiale* F2)
{
    clock_t debut, fin;
    debut = clock();
    Union(F1, F2);
    fin = clock();
    return (double)(fin - debut) / CLOCKS_PER_SEC;
}

int main()
{
    FILE * file = NULL;
    FILE* file2 = NULL;
    FILE * fichier = NULL;
    if ((fichier = fopen("./resultats/resultats_temps_FileBinomialeUnion.txt", "w")) == NULL) {
        printf("Error: not open\n");
        return 0;
    }

    // TESTS DE TEMPS
    int tailles[] = {1000, 5000, 10000, 20000, 50000, 80000, 120000, 200000};
    int nbTailles = sizeof(tailles) / sizeof(tailles[0]);
    char * jeux[8] = 
    {   "./cles_alea/jeu_1_nb_cles_1000.txt",
        "./cles_alea/jeu_1_nb_cles_5000.txt",
        "./cles_alea/jeu_1_nb_cles_10000.txt",
        "./cles_alea/jeu_1_nb_cles_20000.txt",
        "./cles_alea/jeu_1_nb_cles_50000.txt",
        "./cles_alea/jeu_1_nb_cles_80000.txt",
        "./cles_alea/jeu_1_nb_cles_120000.txt",
        "./cles_alea/jeu_1_nb_cles_200000.txt"
    };

     char * jeux2[8] = 
    {   "./cles_alea/jeu_2_nb_cles_1000.txt",
        "./cles_alea/jeu_2_nb_cles_5000.txt",
        "./cles_alea/jeu_2_nb_cles_10000.txt",
        "./cles_alea/jeu_2_nb_cles_20000.txt",
        "./cles_alea/jeu_2_nb_cles_50000.txt",
        "./cles_alea/jeu_2_nb_cles_80000.txt",
        "./cles_alea/jeu_2_nb_cles_120000.txt",
        "./cles_alea/jeu_2_nb_cles_200000.txt"
    };

    for (int i = 0; i < nbTailles; i++) {

        int taille = tailles[i];
        // OUVERTURE
        //printf("%s\n", jeux[i]);
        if((file = fopen(jeux[i], "r")) == NULL)
        {
            printf("Error: not open\n");
            return 0;
        }
        if((file2 = fopen(jeux2[i], "r")) == NULL)
        {
            printf("Error: not open\n");
            return 0;
        }

        Clef128* clefs[taille];
        Clef128* clefs2[taille];
        char buffer[MAX];
        int i = 0, j = 0;

        // LECTURE DES CLES DANS LE FICHIER
        while(fgets(buffer, MAX, file) != NULL)
        {
            //printf("%s\n", buffer);
            Clef128* clef = hexaToUnsigned(buffer);
            clefs[i] = clef;
            i++;
        }

        // LECTURE DES CLES DANS LE FICHIER 2
        while(fgets(buffer, MAX, file2) != NULL)
        {
            Clef128* clef = hexaToUnsigned(buffer);
            clefs2[j] = clef;
            j++;
        }
    
        FileBinomiale* F1 = Construction(clefs, 0, taille);
        FileBinomiale* F2 = Construction(clefs2, 0, taille);

        double tempsUnion = mesurerTempsUnion(F1, F1);

        fprintf(fichier, "Taille: %d, Union: %f\n", taille, tempsUnion);   
        
        // Libérer la mémoire
        deleteClefs(clefs, taille);
        deleteClefs(clefs2, taille);
        deleteFileBinomiale(F1);
        deleteFileBinomiale(F2);
        fclose(file);
    }
}