# Define compiler and compiler options
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -O2 -march=native -g

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