CC = gcc
CFLAGS = -Wall -std=c99 -g

stamp: solve.o validate.o

stamp.o: solve.h validate.h
solve.o: solve.h validate.h
validate.o: validate.h

clean:
	rm -f stamp.o validate.o solve.o
	rm -f stamp
	rm -f output.txt stderr.txt
