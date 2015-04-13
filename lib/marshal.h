#ifndef __MARSHAL_H__
#define __MARSHAL_H__

/* Defines for returned status */
#define STORED          0
#define NOT_STORED      1
#define EXISTS          2
#define NOT_FOUND       3

/* Support KV Store opperations */
typedef enum {
        GET,
        SET
};

/* Operation struct used for gwkv opperations */
struct operation {
        method method_type;
        const char* key;
        size_t key_length;
        const char* value;
        size_t value_length;
}

int
gwkv_marshal_server(struct operation* data, int status, char** ascii);

int
gwkv_marshal_client(struct operation* data, char** ascii);

int
gwkv_demarshal_server(char* ascii, struct** op);

int
gwkv_demarshal_client(char* ascii, struct** op, int* status);
#endif//__MARSHAL_H__
