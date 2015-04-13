#ifndef __HANDLE_OP_H__
#define __HANDLE_OP_H__

#include <stdio.h>
#include <stdlib.h>

#include <./gwkv_ht_wrapper.h>
#include <../lib/marshal.h>

/*
 * handle_operation takes string received from socket
 * and processes it for the GET or SET command.
 *
 * @param int sockfd - the socket descriptor to send data to
 * @param char *msg - the command received from the socket
 *
 * @return int - returns the completion status (success or fail)
 */
int
handle_operation(struct gwkv_server *ht, int sockfd, char *cmd);

int
handle_get(struct gwkv_server *ht, struct operation *op, int sockfd);

#endif
