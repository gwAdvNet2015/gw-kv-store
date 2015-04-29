CC = gcc
CFLAGS = -pthread
DEPS = ../../lib/marshal/marshal.o ../../lib/linkedlist/linkedlist.o ../../lib/hashtable/hashtable.o ../../lib/murmurhash/murmurhash.o ../gwkv_ht_wrapper.o ../server-kv.o ../handle_operation.o
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

test:
	-./test-ht-wrapper
	./server-kv-test &
	sleep 1
	./client-kv-test
	killall server-kv-test

clean:
	rm -f *.o $(TARGET)

