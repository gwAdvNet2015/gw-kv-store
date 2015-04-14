CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -g
DEPS = ../../lib/linkedlist/linkedlist.o ../../lib/hashtable/hashtable.o ../gwkv_ht_wrapper.o
OBJ = test-ht-wrapper

.PHONY: all ht_wrapper_test

all: ht_wrapper_test

rebuild: clean all

ht_wrapper_test:
	$(CC) $(CFLAGS) test_ht_wrapper.c -o $(OBJ) $(DEPS)
clean:
	rm -f $(OBJ)
