#ifndef GWKV_HT_WRAPPER
#define GWKV_HT_WRAPPER

#include <stdlib.h>
#include "../lib/hashtable/hashtable.h"

/* Types of hashing algorithms we support */
typedef enum {
        MD5
} hash_type;

/* All encompassing datatype for server datastore */
struct {
        ht* hashtable;
        hash_type hash;
} gwkv_server;

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
        method method_type;
        const char* key;
        size_t key_length;
        const char* value;
        size_t value_length;
} operation;

/* Defines for hashtable params */
#define HT_SIZE 10 // number of buckets
#define HT_BUCKET_LENGTH 10 // max entry/bucket (only if rebalancing)
#define HT_FILL_PCT 0.1 // % bucket fill (only if rebalancing)
#define HT_REBAL 0 //disable rebalancing for now

/* Initialize a new key/value datastore */
gwkv_server*
gwkv_server_init(hash_type hash_algorithm);

/* Function to perform MD5 hash of key */
static int
gwkv_md5_hash(char* key);

/* Function to compare the equality of two entries */
static int
gwkv_node_cmp(struct ht_node* node1, struct ht_node node2);

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

/* Frees all memory associated with the datastore */
void
gwkv_server_free(gwkv_server* server);

#endif
