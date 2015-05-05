#Use the gcc compiler
CC = gcc
CFLAGS = -g
DEPS = ../lib/marshal/marshal.o client_api.o
LDFLAGS =
#Objects created by makefile
OBJS = client-kv client_api
.PHONY: client_api_test

all: $(OBJS)

rebuild: clean all

client-kv: client-kv.c
	cd ../lib/marshal && make
	$(CC) $(CFLAGS) client-kv.c -o client-kv $(DEPS)

client_api: client_api.c
	$(CC) -c client_api.c -o client_api.o 

client_api_test: client_api_test.c
	make client_api && cd ../lib/marshal && make
	$(CC) $(CFLAGS) client_api_test.c -o client_api_test $(DEPS)

clean:
	@rm -f $(OBJS)

test:
	echo "No Tests Yet."
