CC=gcc
CFLAGS=-O -Wall

all: Universe

sl: Universe.c Universe.h
	$(CC) $(CFLAGS) -o Universe Universe.c -lncurses

clean:
	rm -f Universe

distclean: clean