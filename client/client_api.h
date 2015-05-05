#ifndef __CLIENT_API__
#define __CLIENT_API__

#include "../lib/marshal/marshal.h"

/************************************************
 *                     GW KV
 *  https://github.com/gwAdvNet2015/gw-kv-store
 *
 * Copyright 2015 Lucas Chaufournier, Joel Klein,
 * and Katie Stasaski
 *
 * This program is licensed under the MIT license.
 *
 * client_api.h - sets up functions for client's
 * api
 *************************************************/

int
get_mem(int sockfd, struct operation *msg);

int
send_mem(int sockfd, struct operation * msg);

#endif//__CLIENT_API__
