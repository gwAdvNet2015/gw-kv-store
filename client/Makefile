#Use the gcc compiler
CC = gcc
CFLAGS = -g
DEPS = ../lib/marshal/marshal.o 
LDFLAGS =
#Objects created by makefile
OBJS = client-kv client_api.o

all: $(OBJS)

rebuild: clean all

client_api: client_api.c
	$(CC) -c client_api.c -o client_api.o 

client-kv: client-kv.c
	cd ../lib/marshal && make
	$(CC) $(CFLAGS) client-kv.c -o client-kv $(DEPS)

clean:
	@rm -f $(OBJS)

test:
	echo "No Tests Yet."
