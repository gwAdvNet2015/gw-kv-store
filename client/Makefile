#Use the gcc compiler
CC = gcc
CFLAGS =
DEPS =
LDFLAGS =
#Objects created by makefile
OBJS = #client-kv

#Ensure compiling is done with all necessary dependencies
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJS)

rebuild: clean all

#client-kv: client-kv.c
#	$(CC) $(CFLAGS) -o $@ $^

test:
	@echo "No tests for client"

clean:
	@rm -f $(OBJS)
