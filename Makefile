CC=gcc
CFLAGS=-O3

all: countseq

countseq: main.c
	$(CC) -o countseq main.c $(CFLAGS)

clean:
	rm -f *.o countseq