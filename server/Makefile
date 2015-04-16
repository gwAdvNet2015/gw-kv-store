#Use the gcc compiler
CC = gcc
CFLAGS = -pthread
DEPS = gwkv_ht_wrapper
LDFLAGS =
OBJS = server-kv
SRCS = server-kv.c
WRAPPER_DEPS = gwkv_ht_wrapper.c
WRAPPER_OBJ = ht-wrapper murmurhash

#Ensure compiling is done with all necessary dependencies
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJS)

rebuild: clean all

$(OBJS): ht-wrapper
	$(CC) $(CFLAGS) -o $(OBJS) $(SRCS)

ht-wrapper: gwkv_ht_wrapper.c
	cd ../lib/ && make
	$(CC) $(CFLAGS) -c $(WRAPPER_DEPS)

test:
	cd test && make test

clean:
	@rm -f *.o $(OBJS)
.PHONY: all test
