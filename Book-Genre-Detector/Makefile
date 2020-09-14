CC = gcc
CFLAGS = -Wall -std=c99 -g

tellBookGenre: wordLists.o readBook.o

tellBookGenre.o: readBook.h wordLists.h
readBook.o: readBook.h wordLists.h
wordLists.o: wordLists.h

clean:
	rm -f tellBookGenre.o readBook.o wordLists.o
	rm -f tellBookGenre
	rm -f output.txt stderr.txt
