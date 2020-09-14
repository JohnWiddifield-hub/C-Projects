CC = gcc
CFLAGS = -Wall -std=c99 -g

tracker: command.o model.o

tracker.o: model.h command.h
command.o: model.h command.h
model.o: model.h

clean:
	rm -f tracker.o command.o model.o
	rm -f tracker
	rm -f output.txt stderr.txt
