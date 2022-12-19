# Define compiler and compiler options
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -O2

# Define build rules
all: ./bin/rand-str

./bin/rand-str:
	$(CC) $(CFLAGS) ./src/main.c -o ./bin/rand-str

.PHONEY: run
run:
	./bin/rand-str

.PHONEY: clean
clean:
	rm -f ./bin/rand-str