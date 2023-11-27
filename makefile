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
	$(BIN_DIR)/test_tempsTasArbre

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

# Fichier exécutable
$(BIN_DIR)/test_clef128: $(OBJ_DIR)/test_clef128.o $(OBJ_DIR)/clef128.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/test_tasArbre: $(OBJ_DIR)/test_tasArbre.o $(OBJ_DIR)/tasArbre.o $(OBJ_DIR)/clef128.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN_DIR)/test_tasTableau: $(OBJ_DIR)/test_tasTableau.o $(OBJ_DIR)/tasTableau.o $(OBJ_DIR)/clef128.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ 

$(BIN_DIR)/test_tempsTasTableau: $(OBJ_DIR)/test_tempsTasTableau.o $(OBJ_DIR)/tasTableau.o $(OBJ_DIR)/clef128.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/test_tempsTasArbre: $(OBJ_DIR)/test_tempsTasArbre.o $(OBJ_DIR)/tasArbre.o $(OBJ_DIR)/clef128.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

# Création des répertoires si nécessaire
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Cible pour le nettoyage
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)