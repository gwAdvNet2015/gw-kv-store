#ifndef __MARSHAL_H__

struct operation;

/* Support KV Store opperations */
typedef enum {
        GET,
        SET
} method;

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
gwkv_marshal_client(structu operation* data, char** ascii);

int 
gwkv_demarshal_server(char* ascii, struct** op, int* status);

int 
gwkv_demarshal_client(char* ascii, struct** op, int* status);
#endif//__MARSHAL_H__
