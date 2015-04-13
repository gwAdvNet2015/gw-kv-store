#Use the gcc compiler
CC = gcc
CFLAGS = -pthread
DEPS = ../lib/linkedlist/linkedlist.o ../lib/hashtable/hashtable.o
LDFLAGS =
#Objects created by makefile
OBJS = server-kv

#Ensure compiling is done with all necessary dependencies
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJS)

rebuild: clean all

server-kv: gwkv_ht_wrapper.o server-kv.o
	$(CC) $(CFLAGS) -o $@ $^ $(DEPS)

clean:
	@rm -f *.o $(OBJS)
