#ifndef SERVER_KV_H
#define SERVER_KV_H
#include "gwkv_ht_wrapper.h"
//#include "../lib/shared.h"
#define MAX_CONCURRENCY 1000

/*
enum METHOD {
        GET,
        SET
};*/

/*
struct operation {
        enum METHOD method;
        char *key;
        int key_len;
        char *value;
        int value_len;
};*/

struct pool_list {
	int fd;
	struct pool_list *next;
};

void parse_message(char *message, struct operation *op);
void process_operation(struct gwkv_server *server, struct operation *op, char *message);
void *handle_request(void *ptr);
void server_main(int sockfd, char* thread_number);
#endif
