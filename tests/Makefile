CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -pedantic -O2
INCLUDES = -I../includes
LDFLAGS = -lcunit

TEST_SRC = test_auth.c
TEST_BIN = run_tests

APP_SRCS = ../src/auth.c
APP_OBJS = $(APP_SRCS:.c=.o)

.PHONY: all clean

all: $(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(APP_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(TEST_BIN) $(APP_OBJS)