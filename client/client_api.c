#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include "client_api.h"
/************************************************
 *                     GW KV
 *  https://github.com/gwAdvNet2015/gw-kv-store
 *
 * Copyright 2015 Lucas Chaufournier, Joel Klein,
 * and Katie Stasaski
 *
 * This program is licensed under the MIT license.
 *
 * client_api.c- creates client api and modularizes
 *************************************************/
int
set_mem(int sockfd, struct operation * msg)
{
    char * temp;
    int num_bytes, rc;
    int status = 0;

    gwkv_marshal_client(msg, &temp);

    rc = send(sockfd,temp,strlen(temp), 0);
    if(rc < 0) {
        status = -1;
    }

    return status;
}

int
get_mem(int sockfd, struct operation * msg)
{
    char * temp;
    int num_bytes, rc;
    int status = 0;

    gwkv_marshal_client(msg, &temp);

    rc = send(sockfd,temp,strlen(temp), 0);
    if(rc < 0) {
        status = -1;
        return status;
    }

    status = read_get_msg(sockfd, msg);

    return status;
}

int
read_get_msg(int sockfd, struct operation * msg)
{
    int bytes_received, status;
    
    status = demarshal_msg(sockfd, msg);
    if (status < 0) {
        return -1;  
    } else {
        bytes_received = recv(sockfd, msg->value, msg->value_length, 0);
        return 0;
    }

}

int
demarshal_msg(int sockfd, struct operation * marshal_msg)
{
	char curr_char;
	int count = 0;
	int i;
	char* msg = malloc(1024);
	int * status = malloc(sizeof(int));
    int stat = 0;

    recv(sockfd,&curr_char,1,0);
    if(curr_char == 'E')
    {
        stat = -1;
    } else {
        msg[count] = curr_char;
        count++;

        for(i=0; i<3; i++) {
            while(1) {
                recv(sockfd, &curr_char, 1, 0);
                msg[count] = curr_char;
                count++;

                if(curr_char == ' ') {
                    break;
                }
            }
        }

        while(1) {
            recv(sockfd, &curr_char, 1, 0);
            if (curr_char == '\r') {
                msg[count] = curr_char;
                count++;
                recv(sockfd, &curr_char, 1, 0);
                if (curr_char == '\n') {
                    msg[count] = curr_char;
                    count++;
                    break;
                }
            } else {
                msg[count] = curr_char;
            }
            count++;
        }

    	gwkv_demarshal_client(msg, &marshal_msg, status);
    }
    free(status);
    free(msg); 
	return stat;
}
