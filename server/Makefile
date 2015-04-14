#Use the gcc compiler
CC = gcc
CFLAGS = -g
DEPS = gwkv_ht_wrapper
LDFLAGS =
OBJS = ht-wrapper #server-kv
WRAPPER_DEPS = gwkv_ht_wrapper.c
WRAPPER_OBJ = ht-wrapper murmurhash

#Ensure compiling is done with all necessary dependencies
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJS)

rebuild: clean all

# server-kv: ht-wrapper server-kv.c
#	$(CC) $(CFLAGS) -o $@ $^

ht-wrapper: gwkv_ht_wrapper.c
	cd ../lib/ && make
	$(CC) $(CFLAGS) -c $(WRAPPER_DEPS)

test:
	cd test && make test

clean:
	@rm -f $(OBJS)
.PHONY: all test
