#Use the gcc compiler
CC = gcc
CFLAGS = -pthread
DEPS = gwkv_ht_wrapper
LDFLAGS =
TARGET = server-kv
OBJS = server-kv.o server-kv-run.o
SRCS = server-kv.c server-kv-run.c
WRAPPER_DEPS = gwkv_ht_wrapper.c
WRAPPER_OBJ = ht-wrapper murmurhash

#Ensure compiling is done with all necessary dependencies
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(TARGET)

rebuild: clean all

$(TARGET):build-srcs
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

build-srcs:
	$(CC) $(CFLAGS) -c $(SRCS)

ht-wrapper: gwkv_ht_wrapper.c
	cd ../lib/ && make
	$(CC) $(CFLAGS) -c $(WRAPPER_DEPS)

test:
	cd test && make test

clean:
	@rm -f *.o $(OBJS)
.PHONY: all test
