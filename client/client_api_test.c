#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <inttypes.h>
#include <unistd.h>
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
 * client_api_test.c- test client to test client
 * api
 *************************************************/

int
main(int argc, char ** argv)
{
	char* server_port = "80";
	//ip address or host name of server http request will be sent to
	char* server_ip = "google.com";
	//socket int used to connect
	int sockfd, rc, o;
	//used to store formatted http request
	struct addrinfo hints, *server;
	char * cmd;
	char * key;
	char * value;
    while ((o = getopt (argc, argv, "p:h:c:k:v:")) != -1) {
            switch(o){
            case 'p':
                    server_port = optarg;
                    break;
            case 'h':
                    server_ip = optarg;
                    break;
            case 'c':
                    cmd = optarg;
                    break;
	case 'k':
		key = optarg;
		break;
	case 'v':
		value = optarg;
		break;
            case '?':
                    if(optopt == 'p' || optopt == 'h' ) {
                            fprintf (stderr, "Option %c requires an argument.\n", optopt);
                    }
                    else {
                            fprintf (stderr, "Unknown argument: %c.\n", optopt);
                    }
                    break;
            }
    }
    /* The hints struct is used to specify what kind of server info we are looking for */
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; /* or SOCK_DGRAM */

    /* getaddrinfo() gives us back a server address we can connect to.
       It actually gives us a linked list of addresses, but we'll just use the first.
     */
    if (rc = getaddrinfo(server_ip, server_port, &hints, &server) != 0) {
            perror(gai_strerror(rc));
            exit(-1);
    }

	sockfd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
	if (sockfd == -1) {
		perror("ERROR opening socket");
		exit(-1);
	}
	//printf("socket created\n");
	rc = connect(sockfd, server->ai_addr, server->ai_addrlen);
	if (rc == -1) {
		perror("ERROR on connect");
		close(sockfd);
		exit(-1);
		// TODO: could use goto here for error cleanup
	}

	//read back get value
	if (cmd[0] == 'g') {
		struct operation * msg  = malloc(sizeof (struct operation));
		msg -> method_type = GET;
		msg -> key = key;
		msg -> key_length = strlen(key); 
		get_mem(sockfd,msg);
        printf("Results:  %s:%s\n",msg->key,msg->value);
	}
	else if(cmd[0] == 's'){
		struct operation * msg = malloc(sizeof (struct operation));
		msg -> method_type = SET;
		msg -> key = key;
		msg -> key_length = strlen(key);
		msg -> value = value;
		msg -> value_length = strlen(value);
		set_mem(sockfd,msg);	
        printf("%s:%s\n",msg->key,msg->value);
	}
	out:
		freeaddrinfo(server);
	close(sockfd);

	//printf("Done.\n");
	return 0;

}
