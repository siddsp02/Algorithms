CC = gcc
CFLAGS = -Wall -g

all: algorithm.o tests

algorithm.o:
	$(CC) $(CFLAGS) -c algorithm.c -o algorithm.o

tests: algorithm.o
	$(CC) $(CFLAGS) algorithm.o tests.c -o tests

clean:
	rm -f *.o tests