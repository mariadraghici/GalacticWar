CC=clang
CFLAGS=-Wall -Wextra -std=c99
DEBUG=-g -ggdb -O0 -march=native

build: main

main: main.o GalacticWar.o CircularDoublyLinkedList.o
	$(CC) $(CFLAGS) $(DEBUG) main.o GalacticWar.o CircularDoublyLinkedList.o -o main

CircularDoublyLinkedList.o: CircularDoublyLinkedList.h CircularDoublyLinkedList.c
	$(CC) $(CFLAGS) $(DEBUG) CircularDoublyLinkedList.c -c -o CircularDoublyLinkedList.o

GalacticWar.o: GalacticWar.h GalacticWar.c
	$(CC) $(CFLAGS) $(DEBUG) GalacticWar.c -c -o GalacticWar.o

main.o: main.c
	$(CC) $(CFLAGS) $(DEBUG) main.c -c -o main.o

clean:
	rm *.o
	rm main