# Diretorias
SRC_DIR = src
TEST_DIR = tests
BIN_DIR = bin

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O1 -fno-omit-frame-pointer -g -fsanitize=address -fprofile-arcs -ftest-coverage -I$(SRC_DIR)
LDFLAGS = -lcunit -fsanitize=address -fprofile-arcs -ftest-coverage

# Arquivos fonte
SRC = $(wildcard $(SRC_DIR)/*.c)
SRC_NO_MAIN = $(filter-out $(SRC_DIR)/main.c, $(SRC))

# Executável principal
EXEC = $(BIN_DIR)/jogo

# Executáveis de teste
TEST_EXEC_GAME = $(BIN_DIR)/test_game
TEST_EXEC_IO = $(BIN_DIR)/test_io
TEST_EXEC_BOARD = $(BIN_DIR)/test_board
TEST_EXEC_UNDO = $(BIN_DIR)/test_undo

# Target principal
jogo: $(EXEC)
	$(EXEC)

# Compilar jogo
$(EXEC): $(SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Target principal para testes
testar: $(TEST_EXEC_GAME) $(TEST_EXEC_IO) $(TEST_EXEC_BOARD) $(TEST_EXEC_UNDO)
	$(TEST_EXEC_GAME)
	$(TEST_EXEC_IO)
	$(TEST_EXEC_BOARD)
	$(TEST_EXEC_UNDO)

# Compilar testes separadamente
$(TEST_EXEC_GAME): $(SRC_NO_MAIN) $(TEST_DIR)/test_game.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_EXEC_IO): $(SRC_NO_MAIN) $(TEST_DIR)/test_io.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_EXEC_BOARD): $(SRC_NO_MAIN) $(TEST_DIR)/test_board.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_EXEC_UNDO): $(SRC_NO_MAIN) $(TEST_DIR)/test_undo.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Diretório de relatórios de cobertura
COVERAGE_DIR := coverage-report

# Lista de arquivos fonte para cobertura (sem main.c)
COVERAGE_SRCS := board.c game.c io.c undo.c solver.c

cobertura: limpa $(TEST_EXEC_GAME) $(TEST_EXEC_IO) $(TEST_EXEC_BOARD) $(TEST_EXEC_UNDO)
# Executa os testes
	./$(TEST_EXEC_GAME)
	./$(TEST_EXEC_IO)
	./$(TEST_EXEC_BOARD)
	./$(TEST_EXEC_UNDO)	
# Copia os arquivos fonte para o diretório bin para ajudar o gcov
	mkdir -p $(BIN_DIR)/src
	cp $(SRC_DIR)/*.c $(SRC_DIR)/*.h $(BIN_DIR)/src/ 2>/dev/null || true	
# Gera os relatórios de cobertura para cada arquivo fonte
	cd $(BIN_DIR) && gcov -b -c test_game-board > ../cobertura_board.txt
	cd $(BIN_DIR) && gcov -b -c test_game-game > ../cobertura_game.txt
	cd $(BIN_DIR) && gcov -b -c test_game-io > ../cobertura_io.txt
	cd $(BIN_DIR) && gcov -b -c test_game-undo > ../cobertura_undo.txt	

	cd $(BIN_DIR) && gcov -b -c test_io-board >> ../cobertura_board.txt
	cd $(BIN_DIR) && gcov -b -c test_io-game >> ../cobertura_game.txt
	cd $(BIN_DIR) && gcov -b -c test_io-io >> ../cobertura_io.txt
	cd $(BIN_DIR) && gcov -b -c test_io-undo >> ../cobertura_undo.txt
	
	cd $(BIN_DIR) && gcov -b -c test_board-board >> ../cobertura_board.txt
	cd $(BIN_DIR) && gcov -b -c test_board-game >> ../cobertura_game.txt
	cd $(BIN_DIR) && gcov -b -c test_board-io >> ../cobertura_io.txt
	cd $(BIN_DIR) && gcov -b -c test_board-undo >> ../cobertura_undo.txt

	cd $(BIN_DIR) && gcov -b -c test_undo-board >> ../cobertura_board.txt
	cd $(BIN_DIR) && gcov -b -c test_undo-game >> ../cobertura_game.txt
	cd $(BIN_DIR) && gcov -b -c test_undo-io >> ../cobertura_io.txt
	cd $(BIN_DIR) && gcov -b -c test_undo-undo >> ../cobertura_undo.txt	

# Move os arquivos .gcov para o diretório raiz
	mv $(BIN_DIR)/*.gcov . 2>/dev/null || true

# HTML report
html-coverage: cobertura
	mkdir -p $(COVERAGE_DIR)
	lcov --capture --directory . --output-file $(COVERAGE_DIR)/coverage.info
	genhtml $(COVERAGE_DIR)/coverage.info --output-directory $(COVERAGE_DIR)
	@echo "HTML coverage report generated in $(COVERAGE_DIR)/index.html"

$(BIN_DIR):
	@mkdir -p $@

# Limpar
limpa:
	rm -rf $(BIN_DIR) *.gcno *.gcda *.gcov cobertura_*.txt $(COVERAGE_DIR)

.PHONY: jogo testar cobertura html-coverage limpa