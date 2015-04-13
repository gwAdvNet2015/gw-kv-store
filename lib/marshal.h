#ifndef __MARSHAL_H__

struct operation;

int 
gwkv_marshal_server(struct operation* data, int status, char** ascii);


int 
gwkv_marshal_client(struct operation* data, char** ascii);

int 
gwkv_demarshal_server(char* ascii, struct** op);

int 
gwkv_demarshal_client(char* ascii, struct** op, int* status);
#endif//__MARSHAL_H__
