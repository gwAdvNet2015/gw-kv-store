#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "server-kv.h"
#include "gwkv_ht_wrapper.h"
#include "../lib/hashtable/hashtable.h"
#include "../lib/marshal/marshal.h"

/****************************************
        Author: Tim Wood
        with a little help from
        http://beej.us/guide/bgnet/
****************************************/

#define DEBUG

struct pool_list *list_head = NULL, *list_tail = NULL;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_t threads[MAX_CONCURRENCY];
struct gwkv_server* server;

void
parse_message(char *message, struct operation *op)
{
	struct operation *top;
	gwkv_demarshal_server(message, &top);
	memcpy(op, top, sizeof(struct operation));
	free(top);
        return;
}

void
process_operation(struct gwkv_server *server, struct operation *op, char *message)
{
	char *ht_get;
	int ht_set;

	if (op == NULL) {
		return;
	}

	switch(op->method_type) {
        case GET:
                ht_get = gwkv_server_get(server, op->key, op->key_length, 0);
                if (ht_get == NULL) {
			strcpy(message, "END\r\n");
                }
		else {
			sprintf(message, "VALUE %s 0 %d\r\n%s\r\nEND\r\n\0", 
				op->key, strlen(ht_get), ht_get);
		}
		break;
		
        case SET:
                ht_set = gwkv_server_set(server, op->key, op->key_length, op->value, op->value_length);
                if (ht_set == STORED) {
			strcpy(message, "STORED");
                }
		else if (ht_set == NOT_STORED) {
			strcpy(message, "NOT_STORED");
		}
		break;
        default:
		break;
        }

	
        return;
}


/* Handle a request from a client */
void *
handle_request(void *ptr)
{
        int bytes_read, bytes_write;
        char message[256];
	struct operation op;
	struct pool_list *node;
	int clientfd;

	while (1) {
		pthread_mutex_lock(&mutex);
		while (list_head == NULL) {
			pthread_cond_wait(&cond, &mutex);
		}
		node = list_head;
		list_head = node->next;
		pthread_mutex_unlock(&mutex);
                clientfd = node->fd;
		
		//for test	
		while(1){
		memset(message, 0, sizeof(message));
		bytes_read = read(clientfd, message, 256);
		if(bytes_read < 0) {
			perror("ERROR reading socket");
			break;
		}
		else if (bytes_read == 0){
			#ifdef DEBUG
			printf("Client disconnected.\n");
			#endif
			break;
		}
		else {
			memset(&op, 0, sizeof(struct operation));
			parse_message(message, &op);
			process_operation(server, &op, message);
			bytes_write = strlen(message);
			write(clientfd, message, bytes_write);
			#ifdef DEBUG
			printf("thread: %d, send_message:%s\n", pthread_self(), message);
			#endif
		}
		}

                close(clientfd);
		free(node);
	}
}

/* Main server logic */
void 
server_main(int sockfd, char* thread_number) 
{
	int i, tnum;
	struct pool_list *node;

	/*Create the hash table*/
        server = gwkv_server_init(MURMUR);

        tnum = atoi(thread_number);
	for(i = 0; i < tnum; i++) {
		pthread_create(&threads[i], NULL, handle_request, NULL);
	}

        while(1) {
                struct sockaddr_storage client_addr;
                socklen_t addr_size;
                int clientfd;

                addr_size = sizeof client_addr;
                clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size);
                //sh_print_client_ip(client_addr);
		#ifdef DEBUG
		fprintf(stderr, "accept from client %d\n", clientfd);
		#endif
		node = (struct pool_list *)malloc(sizeof(struct pool_list));
		node->fd = clientfd;
		node->next = NULL;
	
		pthread_mutex_lock(&mutex);
		if (list_head == NULL) {
			list_head = node;
		}
		else {
			list_tail->next = node;
		}
		list_tail = node;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
        }
}

