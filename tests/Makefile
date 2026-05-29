CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -pedantic -O2
INCLUDES = -I../includes
LDFLAGS = -lcunit -lsqlite3

TEST_SRCS = test_auth.c test_drivers.c test_vehicles.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

APP_SRCS = ../src/auth.c ../src/utils.c ../src/drivers.c ../src/vehicles.c ../src/db.c
APP_OBJS = $(APP_SRCS:.c=.o)

TEST_BIN = run_tests

.PHONY: all clean

all: $(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS) $(APP_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(TEST_BIN) $(TEST_OBJS) $(APP_OBJS)
