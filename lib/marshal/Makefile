#Use the gcc compiler
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -g
#List of dependency files needed for compilation
DEPS = marshal.c
LDFLAGS =
OBJS = marshal tests

all: $(OBJS)

rebuild: clean all

marshal:
	$(CC) $(CFLAGS) -c $(DEPS)

tests:
	cd test && make

clean:
	rm -f marshal.o
	cd test && make clean
