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

void parse_message(char *message, int len, struct operation *operation);
void process_operation(struct operation *operation, char *message, int *len);
void *handle_request(void *ptr);
void server_main(int sockfd, char* thread_number);

