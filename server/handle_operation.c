
#include "handle_operation.h"

char*
gwkv_handle_operation(struct gwkv_server *ht, char *cmd)
{
        struct operation *op = malloc( sizeof(struct operation) );
        int status;
        char *ht_set, *ht_get;

        status = gwkv_demarshal_server(cmd, &op);
        if (status == -1) {
                perror("Error on demarshal server");
                exit(-1);
        }

        switch(op->method_type) {
        case GET:
                ht_get = gwkv_handle_get(ht, op);
                if (ht_get == NULL) {
                        perror("Something failed in gwkv_handle_get");
                        exit(-1);
                }
                return ht_get;
        case SET:
                ht_set = gwkv_handle_set(ht, op);
                if (ht_set == NULL) {
                        perror("Something failed in gwkv_handle_set");
                        exit(-1);
                }
                return ht_set;
        default:
                perror("Wrong command, switch dying");
                exit(-1);
        }

        return NULL;
}

char*
gwkv_handle_get(struct gwkv_server *ht, struct operation *op)
{
        char *ht_get;   // returns the value from the hashtable
        char *msg;      // this is the message that gwkv_marshal_server will craft

        ht_get = gwkv_server_get(ht, op->key, op->key_length, op->value_length);
        if (ht_get == NULL) {
                gwkv_craft_message(op, NOT_FOUND, &msg);
        } else {
                op->value = ht_get;
                gwkv_craft_message(op, EXISTS, &msg);
        }

        return msg;
}

char*
gwkv_handle_set(struct gwkv_server *ht, struct operation *op)
{
        int ht_set;     // returns STORED or NOT_STORED from hashtable
        char *msg;      // this is the message that gwkv_marshal_server will craft

        ht_set = gwkv_server_set(ht, op->key, op->key_length, op->value, op->value_length);

        switch(ht_set) {
        case STORED:
                gwkv_craft_message(op, STORED, &msg);
                break;
        case NOT_STORED:
                gwkv_craft_message(op, NOT_STORED, &msg);
                break;
        default:
                perror("gwkv_server_set failed, dying");
                exit(-1);
        }

        return msg;
}

int
gwkv_craft_message(struct operation *op, int status, char **msg)
{
        int res;

        res = gwkv_marshal_server(op, status, msg);

        if (res != 0) {
                return -1;
        } else {
                return 0;
        }
}

