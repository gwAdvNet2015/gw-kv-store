#ifndef GWKV_HT_WRAPPER
#define GWKV_HT_WRAPPER

#include <stdlib.h>

typedef enum {
        GET,
        SET
} method;

/* Defines for result codes */
#define STORED 0
#define NOT_STORED 1
#define EXISTS 2
#define NOT_FOUND 3

struct {
        method method_type,
        const char* key,
        size_t key_length,
        const char* value,
        size_t value_length
} operation;

int
gwkv_memcache_set (memcached_st *ptr,
                  const char *key,
                  size_t key_length,
                  const char *value,
                  size_t value_length);

// Returns NULL on error
char*
gwkv_memcached_get (memcached_st *ptr,
                    const char *key,
                    size_t key_length,
                    size_t *value_length);

#endif
