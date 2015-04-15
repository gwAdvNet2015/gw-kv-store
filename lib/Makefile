DEPS= linkedlist hashtable murmurhash
TEST_DEPS= test_linkedlist test_hashtable test_murmurhash

.PHONY: all test $(DEPS) $(TEST_DEPS)

all: $(DEPS)

test: $(TEST_DEPS)

linkedlist:
	cd linkedlist && make

hashtable:
	cd hashtable && make

murmurhash:
	cd murmurhash && make

marshal:
	cd marshal && make

test_linkedlist:
	cd linkedlist && make test

test_hashtable:
	cd hashtable && make test

test_murmurhash:
	cd murmurhash && make test

test_marshal:
	cd marshal && make test

clean:
	cd linkedlist && make clean
	cd hashtable && make clean
	cd murmurhash && make clean
