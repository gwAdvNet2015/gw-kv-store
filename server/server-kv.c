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
#include "../lib/socket_helper.h" /* Provides sh_* funcs */


/****************************************
        Author: Tim Wood
        with a little help from
        http://beej.us/guide/bgnet/
****************************************/

#define MAX_CONCURRENCY 1000

enum METHOD {
        GET,
        SET
};

struct operation {
        enum METHOD method;
        char *key;
        int key_len;
        char *value;
        int value_len;
};

struct pool_list {
	int fd;
	struct pool_list *next;
} *list_head = NULL, *list_tail = NULL;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_t threads[MAX_CONCURRENCY];

void parse_message(char *message, int len, struct operation *operation) {
        return;
}

void process_operation(struct operation *operation, char *message, int *len) {
        return;
}

/* Handle a request from a client */
void *handle_request(void *ptr){
        int bytes_read, bytes_write;
        char message[256];
	struct operation operation;
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
                bytes_read = read(clientfd, message, 256);
		if(bytes_read < 0) {
			perror("ERROR reading socket");
		}
		else if (bytes_read == 0){
			printf("Client disconnected");
		}
		else {
			parse_message(message, bytes_read, &operation);
			process_operation(&operation, message, &bytes_write);
			write(clientfd, message, bytes_write);
                        printf("thread: %d, received:%s\n", pthread_self(), message);
		}
                //

                close(clientfd);
		free(node);
	}
}


/* Main server logic */
void server_main(int sockfd, char* thread_number) {
	int i, tnum;
	struct pool_list *node;

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
                sh_print_client_ip(client_addr);
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

int main(int argc, char ** argv)
{
        char* server_port = "1234";
        char* thread_number = "2";
        int sockfd;
        int o;

        /* Command line args:
                -p port
                -n thread number
        */
        while ((o = getopt (argc, argv, "p:n:")) != -1) {
                switch(o){
                case 'p':
                        server_port = optarg;
                        break;
                case 'n':
                        thread_number = optarg;
                        break;
                case '?':
                        if(optopt == 'p') {
                                fprintf (stderr, "Option %c requires an argument.\n", optopt);
                        }
                        else {
                                fprintf (stderr, "Unknown argument: %c.\n", optopt);
                        }
                        break;
                }
        }

        printf("listening on port: %s, thread number %s\n", server_port, thread_number);

        sockfd = sh_server(server_port);

	/* Loop forever accepting new connections. */
        server_main(sockfd, thread_number);

        out:
        close(sockfd);

        printf("Done.\n");
        return 0;
}
