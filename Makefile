CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -pedantic -O2
LDFLAGS = -lsqlite3
INCLUDES = -Iincludes

SRC_DIR = src
OBJ_DIR = build
BIN     = app

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean check distcheck

all: $(BIN)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BIN): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

check: all
	@echo "Running make check (no tests yet)"

distcheck: check
	@echo "Running make distcheck (placeholder)"

clean:
	rm -rf $(OBJ_DIR) $(BIN)
