#Use the gcc compiler
CC = gcc
CFLAGS =
DEPS = gwkv_ht_wrapper
LDFLAGS =
#Objects created by makefile
OBJS = server-kv

#Ensure compiling is done with all necessary dependencies
#%.o: %.c $(DEPS)
#	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJS)

rebuild: clean all

server-kv: server-kv.c
	$(CC) $(CFLAGS) -o $@ $^

#ht-wrapper: gwkv_ht_wrapper.c
#	$(CC) $(CFLAGS) -c gwkv_ht_wrapper.c

clean:
	@rm -f $(OBJS)
