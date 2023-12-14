# Définition des répertoires
HEADER_DIR = headers
SRC_DIR = sources
OBJ_DIR = objects
TEST_DIR = tests
BIN_DIR = bin

# Compilateur et drapeaux
CC = gcc
CFLAGS = -I$(HEADER_DIR) -Wall -Wextra -Werror -std=c99 -pedantic -g

# Cible par défaut
all: $(BIN_DIR)/test_clef128 $(BIN_DIR)/test_tasArbre $(BIN_DIR)/test_tasTableau $(BIN_DIR)/test_tempsTasTableau \
	$(BIN_DIR)/test_tempsTasArbre $(BIN_DIR)/test_tempsTasArbreUnion $(BIN_DIR)/test_tempsTasTableauUnion \
	$(BIN_DIR)/test_fonctionHachage $(BIN_DIR)/test_fileBinomiale $(BIN_DIR)/test_tempsFileBinomiale \
	$(BIN_DIR)/test_tempsFileBinomialeUnion $(BIN_DIR)/test_arbreRecherche $(BIN_DIR)/shakespeare \
	$(BIN_DIR)/test_temps_6_16_Construction $(BIN_DIR)/test_temps_6_16_Ajout $(BIN_DIR)/test_temps_6_16_Supp \
	$(BIN_DIR)/test_temps_6_16_Union

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

# Fichier exécutable
$(BIN_DIR)/test_clef128: $(OBJ_DIR)/test_clef128.o $(OBJ_DIR)/clef128.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/test_tasArbre: $(OBJ_DIR)/test_tasArbre.o $(OBJ_DIR)/tasArbre.o $(OBJ_DIR)/clef128.o $(OBJ_DIR)/listeChaine.o| $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN_DIR)/test_tasTableau: $(OBJ_DIR)/test_tasTableau.o $(OBJ_DIR)/tasTableau.o $(OBJ_DIR)/clef128.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ 

$(BIN_DIR)/test_tempsTasTableau: $(OBJ_DIR)/test_tempsTasTableau.o $(OBJ_DIR)/tasTableau.o $(OBJ_DIR)/clef128.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/test_tempsTasTableauUnion: $(OBJ_DIR)/test_tempsTasTableauUnion.o $(OBJ_DIR)/tasTableau.o $(OBJ_DIR)/clef128.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN_DIR)/test_tempsTasArbre: $(OBJ_DIR)/test_tempsTasArbre.o $(OBJ_DIR)/tasArbre.o $(OBJ_DIR)/clef128.o $(OBJ_DIR)/listeChaine.o| $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN_DIR)/test_tempsTasArbreUnion: $(OBJ_DIR)/test_tempsTasArbreUnion.o $(OBJ_DIR)/tasArbre.o $(OBJ_DIR)/clef128.o $(OBJ_DIR)/listeChaine.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN_DIR)/test_fileBinomiale: $(OBJ_DIR)/test_fileBinomiale.o $(OBJ_DIR)/fileBinomiale.o $(OBJ_DIR)/clef128.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN_DIR)/test_tempsFileBinomiale: $(OBJ_DIR)/test_tempsFileBinomiale.o $(OBJ_DIR)/fileBinomiale.o $(OBJ_DIR)/clef128.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN_DIR)/test_tempsFileBinomialeUnion: $(OBJ_DIR)/test_tempsFileBinomialeUnion.o $(OBJ_DIR)/fileBinomiale.o $(OBJ_DIR)/clef128.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN_DIR)/test_fonctionHachage: $(OBJ_DIR)/test_fonctionHachage.o $(OBJ_DIR)/fonctionHachage.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN_DIR)/test_arbreRecherche: $(OBJ_DIR)/test_arbreRecherche.o $(OBJ_DIR)/clef128.o $(OBJ_DIR)/arbreRecherche.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN_DIR)/shakespeare: $(OBJ_DIR)/shakespeare.o $(OBJ_DIR)/fonctionHachage.o $(OBJ_DIR)/listeChaine.o $(OBJ_DIR)/arbreRecherche.o $(OBJ_DIR)/clef128.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN_DIR)/test_temps_6_16_Construction: $(OBJ_DIR)/test_temps_6_16_Construction.o $(OBJ_DIR)/fonctionHachage.o $(OBJ_DIR)/tasArbre.o $(OBJ_DIR)/tasTableau.o $(OBJ_DIR)/fileBinomiale.o $(OBJ_DIR)/clef128.o $(OBJ_DIR)/listeChaine.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN_DIR)/test_temps_6_16_Ajout: $(OBJ_DIR)/test_temps_6_16_Ajout.o $(OBJ_DIR)/fonctionHachage.o $(OBJ_DIR)/tasArbre.o $(OBJ_DIR)/tasTableau.o $(OBJ_DIR)/fileBinomiale.o $(OBJ_DIR)/clef128.o $(OBJ_DIR)/listeChaine.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN_DIR)/test_temps_6_16_Supp: $(OBJ_DIR)/test_temps_6_16_Supp.o $(OBJ_DIR)/fonctionHachage.o $(OBJ_DIR)/tasArbre.o $(OBJ_DIR)/tasTableau.o $(OBJ_DIR)/fileBinomiale.o $(OBJ_DIR)/clef128.o $(OBJ_DIR)/listeChaine.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN_DIR)/test_temps_6_16_Union: $(OBJ_DIR)/test_temps_6_16_Union.o $(OBJ_DIR)/fonctionHachage.o $(OBJ_DIR)/tasArbre.o $(OBJ_DIR)/tasTableau.o $(OBJ_DIR)/fileBinomiale.o $(OBJ_DIR)/clef128.o $(OBJ_DIR)/listeChaine.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

# Création des répertoires si nécessaire
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Cible pour le nettoyage
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)