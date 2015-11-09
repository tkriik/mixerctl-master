CC=		gcc
CFLAGS=		-O2 -std=c99 -Wall -Wextra -Werror
LFLAGS=		-lm
SRC=		mixerctl-master.c
BIN=		mixerctl-master

all:
	$(CC) $(CFLAGS) $(SRC) -o $(BIN) $(LFLAGS)
