#Use the gcc compiler
CC = gcc
CFLAGS = -g
DEPS = ../lib/marshal/marshal.o
LDFLAGS =
#Objects created by makefile
OBJS = client-kv client_api

all: $(OBJS)

rebuild: clean all

client-kv: client-kv.c
	cd ../lib/marshal && make
	$(CC) $(CFLAGS) client-kv.c -o $(OBJS) $(DEPS)

client_api: client_api.c
	cd ../lib/marshal && make
	$(CC) $(CFLAGS) client-kv.c -o $(OBJS) $(DEPS

clean:
	@rm -f $(OBJS)

test:
	echo "No Tests Yet."
