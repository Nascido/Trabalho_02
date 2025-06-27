# Variáveis
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN = simulador
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Alvo padrão
all: $(BIN)

# Regra para criar o diretório de objetos
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compilação dos arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Linkagem final
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Limpeza
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN)
