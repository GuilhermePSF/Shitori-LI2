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

# HTML report directory
COVERAGE_DIR := coverage-report

# Target for HTML coverage report
html-coverage: cobertura
	mkdir -p $(COVERAGE_DIR)
	lcov --capture --directory . --output-file $(COVERAGE_DIR)/coverage.info
	genhtml $(COVERAGE_DIR)/coverage.info --output-directory $(COVERAGE_DIR)
	@echo "HTML coverage report generated in $(COVERAGE_DIR)/index.html"


# Regra de teste + cobertura
cobertura: limpa
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $(filter-out $(SRC_DIR)/main.c, $(SRCS)) $(TEST_SRCS) $(LDFLAGS)
	./$(TEST_EXEC)
	cd $(BIN_DIR) && gcov -b -c testes-board -s ../$(SRC_DIR)
	mv $(BIN_DIR)/board.c.gcov . 2>/dev/null || true
	cat board.c.gcov > cobertura_board.txt

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Limpar
limpa:
	rm -rf $(BIN_DIR) *.gcno *.gcda *.gcov cobertura_board.txt
	rm -f bin/board.gcno bin/board.gcda	

.PHONY: jogo testar cobertura limpa