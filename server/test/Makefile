CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -g -pthread
DEPS = ../../lib/linkedlist/linkedlist.o ../../lib/hashtable/hashtable.o ../../lib/murmurhash/murmurhash.o ../../lib/marshal/marshal.o ../gwkv_ht_wrapper.o ../handle_operation.o  ../gwkv_ht_wrapper.o ../server-kv.o ../handle_operation.o

OBJ = test-ht-wrapper
TARGET = test-ht-wrapper client-kv-test server-kv-test

.PHONY: all test
	
all: $(TARGET) 

rebuild: clean all
	
$(TARGET): build_server 
	$(CC) $(CFLAGS) $(addsuffix .o, $@) $(DEPS) -o $@

build_server: build_src
	cd .. && make

build_src:
	$(CC) $(CFLAGS) -c $(addsuffix .c, $(TARGET))

ht_wrapper_test:
	$(CC)$(CFLAGS) test_ht_wrapper.c -o $(OBJ) $(DEPS)

test:
	-./test-ht-wrapper
	./server-kv-test &
	sleep 1
	./client-kv-test
	killall server-kv-test

clean:
	rm -f *.o $(TARGET)
