#Use the gcc compiler
CC = gcc
CFLAGS =
DEPS = gwkv_ht_wrapper
LDFLAGS =
#Objects created by makefile
OBJS = #server-kv
WRAPPER_DEPS = gwkv_ht_wrapper.c
WRAPPER_OBJ = ht-wrapper

.PHONY: test

#Ensure compiling is done with all necessary dependencies
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJS)

rebuild: clean all

# server-kv: ht-wrapper server-kv.c
#	$(CC) $(CFLAGS) -o $@ $^

ht-wrapper: gwkv_ht_wrapper.c test
	cd ../lib/hashtable && make
	$(CC) $(CFLAGS) -c $(WRAPPER_DEPS)

test:
	cd test && make

clean:
	@rm -f $(OBJS)
