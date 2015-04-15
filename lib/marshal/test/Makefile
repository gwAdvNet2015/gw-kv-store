CC = gcc
CFLAGS = -std=c99 -Wall -pedantic
DEPS = ../marshal.o 
OBJ = test-marshal

all: marshal_test

rebuild: clean all

marshal_test:
	$(CC) $(CFLAGS) test-marshal.c -o $(OBJ) $(DEPS)
clean:
	rm -f $(OBJ)
