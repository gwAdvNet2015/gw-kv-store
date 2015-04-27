#Use the gcc compiler
CC = gcc
CFLAGS = -g  -pthread
LDFLAGS =
TARGET = server-kv
DEPS = ../lib/marshal/marshal.o ../lib/linkedlist/linkedlist.o ../lib/hashtable/hashtable.o ../lib/murmurhash/murmurhash.o gwkv_ht_wrapper.o 
OBJS = server-kv.o server-kv-run.o 
SRCS = server-kv.c server-kv-run.c gwkv_ht_wrapper.c
WRAPPER_DEPS = 
WRAPPER_OBJ = ht-wrapper murmurhash
MARSHAL_DEPS = marshal.c
MARSHAL_OBJ = marshal


#Ensure compiling is done with all necessary dependencies
all: $(TARGET)

rebuild: clean all

$(TARGET):build-srcs 
	cd ../lib/ && make
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(DEPS)

build-srcs:
	$(CC) $(CFLAGS) -c $(SRCS)

test:
	cd test && make test

clean:
	@rm -f *.o $(OBJS)
.PHONY: all test
