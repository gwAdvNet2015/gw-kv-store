#ifndef __MARSHAL_H__
#define __MARSHAL_H__

#include "../shared.h"

#include <stdlib.h>

int
gwkv_marshal_server(struct operation* data, int status, char** ascii);

int
gwkv_marshal_client(struct operation* data, char** ascii);

int
gwkv_demarshal_server(char* ascii, struct operation** op);

int
gwkv_demarshal_client(char* ascii, struct operation** op, int* status);
#endif//__MARSHAL_H__
