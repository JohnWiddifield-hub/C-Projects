CC = gcc
CFLAGS = -g -Wall -std=c99

sales: model.o command.o sales.o

sales.o: model.h command.h

model.o: model.h

command.o: model.h command.h

clean:
	rm -f command.o model.o sales.o
	rm -f sales
	rm -f output.txt
