#include "gwkv_ht_wrapper.h"

gwkv_server*
gwkv_server_init(hash_type hash_algorithm)
{
        
}

static int
gwkv_node_cmp(struct ht_node* node1, struct ht_node node2)
{
	int keycmp = strcmp(node1.key, node2.key);
	int valcmp = strcmp(node1.value, node2.value);
	if(keycmp == 0 && valcmp == 0){ return 0; }
	return 1;
}
