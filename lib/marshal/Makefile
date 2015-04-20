#Use the gcc compiler
CC = gcc
CFLAGS = -g -std=c99 -pedantic -Wall -g
#List of dependency files needed for compilation
DEPS = marshal.c
LDFLAGS =
OBJS = marshal tests

.PHONY: test
all: $(OBJS)

rebuild: clean all

marshal:
	$(CC) $(CFLAGS) -c $(DEPS)

tests:
	cd test && make

test:
	cd test && make test

clean:
	rm -f marshal.o
	cd test && make clean
