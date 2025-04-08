# Diretórios
SRC_DIR := src
TESTES_DIR := tests
BIN_DIR := bin

# Compilador
CC := gcc
CFLAGS := -Wall -Wextra -pedantic -O1 -fno-omit-frame-pointer -g -fsanitize=address -I$(SRC_DIR)
LDFLAGS := -lcunit -fsanitize=address

# Arquivos fonte e de teste
SRCS := $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS := $(wildcard $(TESTES_DIR)/*.c)

# Nome dos executáveis
EXEC := $(BIN_DIR)/jogo
TEST_EXEC := $(BIN_DIR)/testes

# Compilar e executar o jogo
jogo: $(EXEC)
	$(EXEC)

$(EXEC): $(SRCS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compilar e executar os testes
teste: $(TEST_EXEC)
	$(TEST_EXEC)

$(TEST_EXEC): $(filter-out $(SRC_DIR)/main.c, $(SRCS)) $(TEST_SRCS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilar com cobertura de código
cobertura: CFLAGS += -fprofile-arcs -ftest-coverage
cobertura: $(TEST_EXEC)
	$(TEST_EXEC)
	@gcov -b -c $(SRC_DIR)/*.c > cobertura.txt

# Criar diretório de binários, se não existir
$(BIN_DIR):
	@mkdir -p $@

# Limpeza dos ficheiros gerados
limpa:
	rm -rf $(BIN_DIR) *.gcno *.gcda *.gcov cobertura.txt

.PHONY: jogo teste cobertura limpa