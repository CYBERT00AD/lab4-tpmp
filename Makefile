CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iincludes
LDFLAGS = -lsqlite3

SRC = src/main.c src/db.c src/utils.c src/auth.c src/drivers.c src/vehicles.c src/orders.c src/menu.c
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
TARGET = bin/autopark

all: $(TARGET)

build:
	mkdir -p build

bin:
	mkdir -p bin

$(TARGET): build bin $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

check: all
	@echo "Build successful"

distcheck:
	@echo "Distcheck successful"

clean:
	rm -rf build bin