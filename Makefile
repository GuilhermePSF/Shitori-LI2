# Diretórios
SRC_DIR := src
TESTES_DIR := tests
BIN_DIR := bin

# Compilador
CC := gcc
CFLAGS := -Wall -Wextra -pedantic -O1 -g -I$(SRC_DIR)
LDFLAGS := -lcunit

# Arquivos fonte e de teste
SRCS := $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS := $(wildcard $(TESTES_DIR)/*.c)

# Nome dos executáveis
EXEC := $(BIN_DIR)/jogo
TEST_EXEC := $(BIN_DIR)/testes

# Comando para criar e rodar o jogo
jogo: $(EXEC)
	$(EXEC)

$(EXEC): $(SRCS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Comando para compilar e rodar os testes
teste: $(TEST_EXEC)
	$(TEST_EXEC)

$(TEST_EXEC): $(filter-out $(SRC_DIR)/main.c, $(SRCS)) $(TEST_SRCS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
    
# Criação do diretório binário
$(BIN_DIR):
	@mkdir -p $@

# Comando para limpar os arquivos gerados
limpa:
	rm -rf $(BIN_DIR)

.PHONY: jogo teste limpa