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

void *handle_request(void *ptr);
void server_main(int sockfd, char* thread_number);

