#define __DEBUG__ 1

#include <handle_operation.h>

int
parse_command(struct gwkv_server *ht, int sockfd, char *cmd)
{
        struct operation *op = malloc( sizeof(struct operation) );
        int status, ht_res, ht_get;

        status = gwkv_demarshal_server(cmd, &op);
        if (status == -1) {
                perror("Error on demarshal server");
                exit(-1);
        }

#ifdef __DEBUG__
        printf("command is %d\n", op->method_type);
#endif

        switch(op->method_type) {
        case GET:
                int ht_get = handle_get(ht, op, sockfd);
                break;
        case SET:
        default:
                perror("Wrong command, switch dying");
                exit(-1);
        }

        return 0;
}

int
handle_get(struct gwkv_server *ht, struct operation *op, int sockfd)
{
        char *ht_get;

        ht_get = gwkv_server_get(ht, op->key, op->key_length, op->value_length);
        if (ht_get == NULL) {
                perror("Value not in server");
                        // TODO: send client that no data
                } else {
#ifdef __DEBUG__
                        printf("Retrieved data - %s\n", ht_get);
#endif
                         // TODO: send client data
                }
}
