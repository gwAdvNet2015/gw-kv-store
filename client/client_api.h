#ifndef __CLIENT_API__
#define __CLIENT_API__

#include "../lib/marshal/marshal.h"


int
get_mem(int sockfd, struct operation *msg);

int
send_mem(int sockfd, struct operation * msg);

#endif//__CLIENT_API__
