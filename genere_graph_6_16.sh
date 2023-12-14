#!/bin/bash

make clean
make
./bin/test_temps_6_16_Ajout
./bin/test_temps_6_16_Construction
./bin/test_temps_6_16_Supp
./bin/test_temps_6_16_Union
gnuplot ./resultats/gnuplot_6_16_Ajout
gnuplot ./resultats/gnuplot_6_16_Construction
gnuplot ./resultats/gnuplot_6_16_Suppression
gnuplot ./resultats/gnuplot_6_16_Union