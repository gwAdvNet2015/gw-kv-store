#ifndef SERVER_KV_H
#define SERVER_KV_H
#include "gwkv_ht_wrapper.h"
//#include "../lib/shared.h"
#define MAX_CONCURRENCY 1000

struct pool_list {
	int fd;
	struct pool_list *next;
};

// This is the hashtable on the server
struct gwkv_server *ht;

void *handle_request(void *ptr);
void server_main(int sockfd, char* thread_number);
#endif
