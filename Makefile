CC=		gcc
CFLAGS=		-O2 -ansi -pedantic -Wall -Wextra -Werror
LFLAGS=		-lm
SRC=		mixerctl-master.c
BIN=		mixerctl-master

all:
	$(CC) $(CFLAGS) $(SRC) -o $(BIN) $(LFLAGS)

.PHONY: clean

clean:
	rm -f $(BIN)
