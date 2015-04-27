#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "../lib/socket_helper.h" /* Provides sh_* funcs */
#include "server-kv.h"
#include "gwkv_ht_wrapper.h"
#include "../lib/hashtable/hashtable.h"

/****************************************
        Author: Tim Wood
        with a little help from
        http://beej.us/guide/bgnet/
****************************************/

int
main(int argc, char ** argv)
{
        char* server_port = "1234";
        char* thread_number = "2";
        int sockfd;
        int o;

        /* Command line args:
                -p port
                -n thread number
        */
        while ((o = getopt (argc, argv, "p:n:")) != -1) {
                switch(o){
                case 'p':
                        server_port = optarg;
                        break;
                case 'n':
                        thread_number = optarg;
                        break;
                case '?':
                        if(optopt == 'p') {
                                fprintf (stderr, "Option %c requires an argument.\n", optopt);
                        }
                        else {
                                fprintf (stderr, "Unknown argument: %c.\n", optopt);
                        }
                        break;
                }
        }

        printf("listening on port: %s, thread number %s\n", server_port, thread_number);

        sockfd = sh_server(server_port);

	/* Loop forever accepting new connections. */
        server_main(sockfd, thread_number);

        out:
        close(sockfd);

        printf("Done.\n");
        return 0;
}

