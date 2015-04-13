#include "gwkv_ht_wrapper.h"

gwkv_server*
gwkv_server_init(hash_type hash_algorithm)
{
        
}

static int
gwkv_murmur_hash(char* key){
	return murmurhash(key, strlen(key), 0);//takes in the key, the length of the key, and a seed
}
