#ifndef GWKV_HT_WRAPPER
#define GWKV_HT_WRAPPER

#include <stdlib.h>
#include "../hashtable/hashtable.h"

/* Operations the table supports */
typedef enum {
        GET,
        SET
} method;

/* Defines for result codes */
#define STORED 0
#define NOT_STORED 1
#define EXISTS 2
#define NOT_FOUND 3

/* Datatype for wrapping datastore values */
struct {
        method method_type,
        const char* key,
        size_t key_length,
        const char* value,
        size_t value_length
} operation;

/**
 * Wrapper function to set a value in the hashtable
 * Returns either STORED or NOT_STORED (defined above)
 */
int
gwkv_server_set (memcached_st *ptr,
                 const char *key,
                 size_t key_length,
                 const char *value,
                 size_t value_length);

/**
 * Wrapper function to read a value from the hashtable
 * Returns the data if sucessful, or NULL on error
 * These correspond to the EXISTS and NOT_FOUND codes above
 */
char*
gwkv_server_get (memcached_st *ptr,
                 const char *key,
                 size_t key_length,
                 size_t *value_length);



#endif
