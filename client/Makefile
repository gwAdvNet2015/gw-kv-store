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
	$(CC) $(CFLAGS) client-kv.c -o client-kv $(DEPS)

client_api: client_api.c
	cd ../lib/marshal && make
	$(CC) $(CFLAGS) client_api.c -o client_api $(DEPS)

clean:
	@rm -f $(OBJS)

test:
	echo "No Tests Yet."
