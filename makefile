# Définition des répertoires
HEADER_DIR = headers
SRC_DIR = sources
OBJ_DIR = objets
TEST_DIR = tests
BIN_DIR = bin

# Compilateur et drapeaux
CC = gcc
CFLAGS = -I$(HEADER_DIR) -Wall

# Fichiers sources, objets et tests
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TESTS = $(wildcard $(TEST_DIR)/*.c)

# Nom de l'exécutable principal et du test
EXEC = $(BIN_DIR)/main
TEST_EXEC = $(BIN_DIR)/test_tasTableau

# Cible par défaut
all: $(EXEC)

# Création de l'exécutable
$(EXEC): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compilation des fichiers source en objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Création des répertoires si nécessaire
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Cible pour le nettoyage
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Cibles pour les tests
test: $(TEST_EXEC)

$(TEST_EXEC): $(OBJS) $(TESTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Marquer les cibles qui ne représentent pas des fichiers
.PHONY: all clean test