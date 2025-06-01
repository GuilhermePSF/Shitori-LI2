# Diretórios
SRC_DIR = src
HDR_DIR = $(SRC_DIR)/hdr
TEST_DIR = tests
BIN_DIR = bin
COVERAGE_DIR = coverage-report

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O1 -fno-omit-frame-pointer -g -fsanitize=address -fprofile-arcs -ftest-coverage -I$(SRC_DIR) -I$(HDR_DIR)
LDFLAGS = -lcunit -fprofile-arcs -ftest-coverage

SRC = $(wildcard $(SRC_DIR)/*.c) 
SRC_NO_MAIN = $(filter-out $(SRC_DIR)/main.c, $(SRC))

# Executável principal
EXEC = $(BIN_DIR)/jogo

# Executável único para todos os testes
TEST_EXEC = $(BIN_DIR)/tests

.PHONY: all jogo testar cobertura html-coverage complexidade limpa

all: jogo

# Compilar jogo
$(EXEC): $(SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

jogo: $(EXEC)
	clear; $(EXEC)

# Compilar todos os testes em um único executável
$(TEST_EXEC): $(SRC_NO_MAIN) $(TEST_DIR)/test.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

testar: $(TEST_EXEC)
	$(TEST_EXEC)

cobertura: testar
	@echo "Capturando dados de cobertura com lcov..."
	lcov --directory . --capture --output-file coverage.info
	lcov --remove coverage.info '/usr/*' 'tests/*' --output-file coverage_filtered.info
	@echo "Gerando relatório HTML..."
	genhtml coverage_filtered.info --output-directory $(COVERAGE_DIR)
	mv coverage.info coverage_filtered.info $(COVERAGE_DIR)
	@echo "Relatório disponível em $(COVERAGE_DIR)/index.html"

$(BIN_DIR):
	@mkdir -p $@

complexidade:
	@printf "Modified McCabe Cyclomatic Complexity\n"
	@printf "|   Traditional McCabe Cyclomatic Complexity\n"
	@printf "|       |    n Statements in function\n"
	@printf "|       |       |   First line of function\n"
	@printf "|       |       |       |   n lines in function\n"
	@printf "|       |       |       |       |  filename(definition line number):function\n"
	@printf "|       |       |       |       |       |\n"
	@pmccabe $(SRC)

limpa:
	clear; rm -rf $(BIN_DIR) *.gcno *.gcda $(COVERAGE_DIR)