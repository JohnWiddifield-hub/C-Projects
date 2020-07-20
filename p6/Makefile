CC = gcc
CFLAGS = -Wall -std=c99 -g

search: parse.o pattern.o

search.o: pattern.h parse.h
parse.o: parse.h pattern.h
pattern.o: pattern.h


clean:
	rm -f pattern.o search.o parse.o
	rm -f search
	rm -f output.txt stderr.txt stdout.txt estderr.txt
