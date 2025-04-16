# Diretorias
SRC_DIR = src
TEST_DIR = tests
BIN_DIR = bin

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O1 -fno-omit-frame-pointer -g -fsanitize=address -I$(SRC_DIR)
LDFLAGS = -lcunit -fsanitize=address

SRC = $(wildcard $(SRC_DIR)/*.c)
SRC_NO_MAIN = $(filter-out $(SRC_DIR)/main.c, $(SRC))
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)

# Executáveis
EXEC = $(BIN_DIR)/jogo
TEST_EXEC = $(BIN_DIR)/testes

# Target principal
jogo: $(EXEC)
	$(EXEC)

# Compilar jogo
$(EXEC): $(SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compilar testes
testar: $(TEST_EXEC)
	$(TEST_EXEC)

$(TEST_EXEC): $(SRC_NO_MAIN) $(TEST_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Cobertura
cobertura: CFLAGS += -fprofile-arcs -ftest-coverage
cobertura: $(TEST_EXEC)
	$(TEST_EXEC)
	@gcov -b -c $(SRC_DIR)/*.c > cobertura.txt

# Criar diretoria para os executaveis
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Limpar
limpa:
	rm -rf $(BIN_DIR) *.gcno *.gcda *.gcov cobertura.txt

.PHONY: jogo testar cobertura limpa
