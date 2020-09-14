CC = gcc
CFLAGS = -Wall -std=c99 -g

all: deflate inflate

deflate: filebuffer.o cipher.o

deflate.o: filebuffer.h cipher.h
filebuffer.o: cipher.h filebuffer.h
cipher.o: cipher.h


inflate: filebuffer.o cipher.o

inflate.o: filebuffer.h cipher.h
filebuffer.o: cipher.h filebuffer.h
cipher.o: cipher.h


clean:
	rm -f inflate.o deflate.o filebuffer.o cipher.o
	rm -f inflate deflate
	rm -f output.txt stderr.txt stdout.txt estderr.txt
