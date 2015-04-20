CC = gcc
CFLAGS = -std=c99 -Wall -pedantic
DEPS = ../linkedlist.o
OBJ = test-linkedlist

.PHONY: test
all: linkedlist_test

rebuild: clean all

linkedlist_test:
	$(CC) $(CFLAGS) test-ll.c -o $(OBJ) $(DEPS)

test:
	./test-linkedlist

clean:
	rm -f $(OBJ)
