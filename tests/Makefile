CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -pedantic -O2
INCLUDES = -I../includes
LDFLAGS = -lcunit

TEST_SRC = test_auth.c
TEST_BIN = run_tests

.PHONY: all clean

all: $(TEST_BIN)

$(TEST_BIN): $(TEST_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TEST_BIN)
