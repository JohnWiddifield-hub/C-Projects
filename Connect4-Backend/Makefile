CC = gcc
CFLAGS = -g -Wall -std=c99 

connect4: connect4.o board.o check.o
	gcc connect4.o board.o check.o -o connect4

connect4.o: connect4.c board.h check.h
	gcc -Wall -std=c99 -c connect4.c

board.o: board.c board.h
	gcc -Wall -std=c99 -c board.c

check.o: check.c check.h
	gcc -Wall -std=c99 -c check.c

clean:
	rm -f connect4.o check.o board.o
	rm -f connect4
	rm -f output.txt
