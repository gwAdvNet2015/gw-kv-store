#Use the gcc compiler
CC = gcc
CFLAGS =
DEPS = ../lib/marshal/marshal.o
LDFLAGS =
#Objects created by makefile
OBJS = client-kv

all: $(OBJS)

rebuild: clean all

client-kv: client-kv.c
	cd ../lib/marshal && make
	$(CC) $(CFLAGS) client-kv.c -o $(OBJS) $(DEPS)

clean:
	@rm -f $(OBJS)
