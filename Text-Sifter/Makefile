CC = gcc
CFLAGS = -g -Wall -std=c99 

select: select.o match.o text.o

select.o: match.h text.h

match.o: match.h text.h

text.o: text.h

clean:
	rm -f select.o match.o text.o
	rm -f select
	rm -f output.txt
