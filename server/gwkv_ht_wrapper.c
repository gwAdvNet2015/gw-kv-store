#include <assert.h>
#include <stdlib.h>

#include "../lib/hashtable/hashtable.h"
#include "gwkv_ht_wrapper.h"

struct gwkv_server*
gwkv_server_init(hash_type hash_algorithm)
{
        /* First, allocate memory */
        struct gwkv_server *server = malloc(sizeof(struct gwkv_server));
        if(!server){
                return NULL;
        }

        /* Set the hash function according to input */
        HASH_FUNC;
        server->hash = hash_algorithm;
        switch(hash_algorithm){
                /* Currently, only one type of hashing */
                default:
                case MD5:
                        hash_func = &gwkv_md5_hash;
                        break;
        }

        server->hashtable = ht_init(HT_SIZE, HT_BUCKET_LENGTH, HT_FILL_PCT, HT_REBAL, hash_func, &gwkv_node_cmp);
        if(!server->hashtable){
                /* Failure malloc-ing hashtable memory. Die here */
                free(server);
                return NULL;
        }

        return server;
}

int
gwkv_server_set(struct gwkv_server* server,
                char* key,
                size_t key_length,
                char* value,
                size_t value_length)
{
        /* Variable defines */
        int expected_size;
        struct ht_node* existing_node;

        /* Precondition checks */
        if(!server || !server->hashtable || !key || !value){
                return NOT_STORED;
        }

        expected_size = server->hashtable->node_count;
        existing_node = ht_lookup(server->hashtable, key);
        if(existing_node){
                /* Node already exists in the table, update its value */
                existing_node->value = value;
        }else{
                /* Node does not exist, add it */
                existing_node = ht_create_node(key, value);
                ht_insert(server->hashtable, existing_node);
                expected_size++;
        }

        /* TODO if we want to support auto-rebalancing the hastable, do so here
        if(ht_check_rebalance(server->hashtable)){
                ht_rebalance(&server->hashtable);
        }
        */

        /* Now, sanity check to ensure the node was actually entered */
        if(existing_node && server->hashtable->node_count == expected_size){
                return STORED;
        }else{
                return NOT_STORED;
        }
}

char*
gwkv_server_get(struct gwkv_server* server,
                char* key,
                size_t key_length,
                size_t value_length)
{
        struct ht_node* node;

        /* Precondition checks */
        if(!server || !server->hashtable || !key){
                return NULL;
        }

        node = ht_lookup(server->hashtable, key);
        if(!node){
                /* Node does not exist in table */
                return NULL;
        }

        void* data = node->value;
        if(!data){
                return NULL;
        }

        /* We only care about storing char* so we can cast here */
        return (char*)data;
}

void
gwkv_server_free(struct gwkv_server* server)
{
        ht_free(server->hashtable);
        free(server);
}

int
gwkv_md5_hash(char* key)
{
        // Temporary value
        return 0;
}

int
gwkv_node_cmp(struct ht_node* node1, struct ht_node* node2)
{
        // Temporary value
        return 0;
}
