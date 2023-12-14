#!/bin/bash

make clean
make
./bin/test_tempsTasTableau
./bin/test_tempsTasTableauUnion
./bin/test_tempsTasArbre
./bin/test_tempsTasArbreUnion
./bin/test_tempsFileBinomiale
./bin/test_tempsFileBinomialeUnion
gnuplot ./resultats/gnuplot_FileBinomiale
gnuplot ./resultats/gnuplot_FileBinomialeUnion
gnuplot ./resultats/gnuplot_TasArbre
gnuplot ./resultats/gnuplot_TasArbreUnion
gnuplot ./resultats/gnuplot_TasTableau
gnuplot ./resultats/gnuplot_TasTableauUnion