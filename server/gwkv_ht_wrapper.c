#include <assert.h>
#include <stdlib.h>

#include "gwkv_ht_wrapper.h"

struct gwkv_server*
gwkv_server_init(hash_type hash_algorithm)
{
        /* First, allocate memory */
        struct gwkv_server *server = malloc(sizeof(struct gwkv_server));
        assert(server);

        /* Set the hash function according to input */
        HASH_FUNC;
        server->hash = hash_algorithm;
        switch(hash_algorithm){
                /* Currently, only one type of hashing */
                default:
                case MD5:
                        hash_func = &gwkv_md5_hash;
        }

        server->hashtable = ht_init(HT_SIZE, HT_BUCKET_LENGTH, HT_FILL_PCT, HT_REBAL, hash_func, &gwkv_node_cmp);
        assert(server->hashtable);

        return server;
}

void
gwkv_server_free(struct gwkv_server* server)
{
        ht_free(server->hashtable);
        free(server);
}
