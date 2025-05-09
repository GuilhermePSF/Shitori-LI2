# Diretórios
SRC_DIR = src
TEST_DIR = tests
BIN_DIR = bin
COVERAGE_DIR = coverage-report

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O1 -fno-omit-frame-pointer -g -fsanitize=address -fprofile-arcs -ftest-coverage -I$(SRC_DIR)
LDFLAGS = -lcunit -fprofile-arcs -ftest-coverage

SRC = $(wildcard $(SRC_DIR)/*.c) 
SRC_NO_MAIN = $(filter-out $(SRC_DIR)/main.c, $(SRC))

# Executável principal
EXEC = $(BIN_DIR)/jogo

# Executáveis de teste
TEST_EXEC_TIP = $(BIN_DIR)/test_tip
TEST_EXEC_GAME = $(BIN_DIR)/test_game
TEST_EXEC_IO = $(BIN_DIR)/test_io
TEST_EXEC_BOARD = $(BIN_DIR)/test_board
TEST_EXEC_UNDO = $(BIN_DIR)/test_undo
TEST_EXEC_VERIFICA = $(BIN_DIR)/test_verifica
TEST_EXEC_SOLVER = $(BIN_DIR)/test_solver

.PHONY: all jogo testar cobertura html-coverage limpa

all: jogo

# Compilar jogo
$(EXEC): $(SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

jogo: $(EXEC)
	$(EXEC)

# Compilar testes
$(TEST_EXEC_TIP): $(SRC_NO_MAIN) $(TEST_DIR)/test_tip.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_EXEC_GAME): $(SRC_NO_MAIN) $(TEST_DIR)/test_game.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_EXEC_IO): $(SRC_NO_MAIN) $(TEST_DIR)/test_io.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_EXEC_BOARD): $(SRC_NO_MAIN) $(TEST_DIR)/test_board.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_EXEC_UNDO): $(SRC_NO_MAIN) $(TEST_DIR)/test_undo.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_EXEC_VERIFICA): $(SRC_NO_MAIN) $(TEST_DIR)/test_verifica.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_EXEC_SOLVER): $(SRC_NO_MAIN) $(TEST_DIR)/test_solver.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

testar: $(TEST_EXEC_SOLVER) $(TEST_EXEC_GAME) $(TEST_EXEC_IO) $(TEST_EXEC_BOARD) $(TEST_EXEC_TIP) $(TEST_EXEC_UNDO) $(TEST_EXEC_VERIFICA)
	$(TEST_EXEC_SOLVER)
	$(TEST_EXEC_TIP)
	$(TEST_EXEC_GAME)
	$(TEST_EXEC_IO)
	$(TEST_EXEC_BOARD)
	$(TEST_EXEC_UNDO)
	$(TEST_EXEC_VERIFICA)

cobertura: testar
	@echo "Capturando dados de cobertura com lcov..."
	lcov --directory . --capture --output-file coverage.info
	lcov --remove coverage.info '/usr/*' 'tests/*' --output-file coverage_filtered.info
	@echo "Gerando relatório HTML..."
	genhtml coverage_filtered.info --output-directory $(COVERAGE_DIR)
	@mv coverage.info coverage_filtered.info $(COVERAGE_DIR)
	@echo "Relatório disponível em $(COVERAGE_DIR)/index.html"

$(BIN_DIR):
	@mkdir -p $@

limpa:
	rm -rf $(BIN_DIR) *.gcno *.gcda $(COVERAGE_DIR)