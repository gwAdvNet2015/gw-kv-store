CC = gcc
CFLAGS = -Wall
DEPS = ../../lib/linkedlist/linkedlist.o ../../lib/hashtable/hashtable.o ../../lib/murmurhash/murmurhash.o ../gwkv_ht_wrapper.o
OBJ = test-ht-wrapper
OBJ_C = client-kv-test
OBJ_S = server-kv-test
DEP_S = server-kv

.PHONY: all test

all: ht_wrapper_test client-server-kv-test

rebuild: clean all

ht_wrapper_test:
	$(CC) $(CFLAGS) test_ht_wrapper.c -o $(OBJ) $(DEPS)

client-server-kv-test:
	$(CC) $(CFLAGS) -o $(OBJ_C) $(addsuffix .c, $(OBJ_C))
	$(CC) $(CFLAGS) -c $(addsuffix .c, $(OBJ_S))
	$(CC) $(CFLAGS) -c ../$(addsuffix .c, $(DEP_S))
	$(CC) $(CFLAGS) -o $(OBJ_S) $(addsuffix .o, $(OBJ_S)) $(addsuffix .o, $(DEP_S))

test: ht_wrapper_test client-server-kv-test
	./test-ht-wrapper
	./server-kv-test &
	sleep 1
	./client-kv-test

clean:
	rm -f *.o $(OBJ) $(OBJ_C) $(OBJ_S)
