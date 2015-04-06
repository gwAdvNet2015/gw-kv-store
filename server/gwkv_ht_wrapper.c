#include <assert.h>

#include "gwkv_ht_wrapper.h"

gwkv_server*
gwkv_server_init(hash_type hash_algorithm)
{
        /* First, allocate memory */
        gwkv_server* server = malloc(sizeof(gwkv_server));
        assert(gwkv_server);

        /* Set the hash function according to input */
        HASH_FUNC hash_function;
        server->hash_type = hash_algorithm;
        switch(hash_algorithm){
                /* Currently, only one type of hashing */
                default:
                case MD5:
                        hash_function = &gwkv_md5_hash;
        }

        server->ht = ht_init(HT_SIZE, HT_BUCKET_LENGTH, HT_FILL_PCT, HT_REBAL, hash_function, &gwkv_node_cmp);
        assert(server->ht);
}

void
gwkv_server_free(gwkv_server* server)
{
        ht_free(server->ht);
        free(server);
}
