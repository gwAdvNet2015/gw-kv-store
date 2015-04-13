/* File to test hashtable wrapper */

#include <assert.h>
#include "../gwkv_ht_wrapper.h"
#include "../../lib/hashtable/hashtable.h"

int
main(){
        struct gwkv_server* server = gwkv_server_init(MD5);
        assert(server);

        gwkv_server_free(server);
}
