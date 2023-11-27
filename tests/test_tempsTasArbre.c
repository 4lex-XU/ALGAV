#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/clef128.h"
#include "../headers/tasArbre.h"
#include <time.h>
#include <math.h>

#define MAX 1000

double mesurerTempsAjoutsIteratifs(Clef128 **clefs, int len)
{
    clock_t debut, fin;
    debut = clock();
    TasArbre* t = ajoutsIteratifs(clefs, len, 1);
    fin = clock();
    delete(t);
    return (double)(fin - debut) / CLOCKS_PER_SEC;
}

double mesurerTempsConstruction(Clef128 **clefs, int len)
{
    clock_t debut, fin;
    debut = clock();
    TasArbre* t = construction(clefs, len);
    fin = clock();
    delete(t);
    return (double)(fin - debut) / CLOCKS_PER_SEC;
}

int main(int argc, char** argv)
{
    FILE * file = NULL;
    FILE * fichier = NULL;
    if ((fichier = fopen("./resultats/resultats_temps_TasArbre.txt", "w")) == NULL) {
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

    for (int i = 0; i < nbTailles; i++) {

        int taille = tailles[i];
        // OUVERTURE
        //printf("%s\n", jeux[i]);
        if((file = fopen(jeux[i], "r")) == NULL)
        {
            printf("Error: not open\n");
            return 0;
        }
        
        Clef128* clefs[taille];
        char buffer[MAX];
        int i = 0;

        // LECTURE DES CLES DANS LE FICHIER
        while(fgets(buffer, MAX, file) != NULL)
        {
            //printf("%s\n", buffer);
            Clef128* clef = hexaToUnsigned(buffer);
            clefs[i] = clef;
            i++;
        }
        double tempsAjoutsIteratifs = mesurerTempsAjoutsIteratifs(clefs, taille);
        double tempsConstruction = mesurerTempsConstruction(clefs, taille);

        fprintf(fichier, "Taille: %d, ajoutsIteratifs: %f, construction: %f\n", taille, tempsAjoutsIteratifs, tempsConstruction);   
        
        // Libérer la mémoire
        deleteClefs(clefs, taille);
        fclose(file);
    }
}