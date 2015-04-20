#Use the gcc compiler
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall
#List of dependency files needed for compilation
DEPS = linkedlist.c
LDFLAGS =
OBJS = linkedlist tests

.PHONY: test
all: $(OBJS)

rebuild: clean all

linkedlist:
	$(CC) $(CFLAGS) -c $(DEPS)

tests:
	cd test && make

test:
	cd test && make test

clean:
	rm -f linkedlist.o
	cd test && make clean
