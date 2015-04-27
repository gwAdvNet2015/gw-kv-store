#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include "../../lib/socket_helper.h" /* Provides sh_* funcs */

/****************************************
        Author: Tim Wood
        with a little help from
        http://beej.us/guide/bgnet/
****************************************/

int 
client_request(int sockfd, char* message) 
{
        int rc;
        int temp_f;
        float temp_c;
        /* Send the message, plus the \0 string ending. Use 0 flags. */

        rc = send(sockfd, message, strlen(message)+1, 0);
        if(rc < 0) {
                perror("ERROR on send");
                exit(-1);
        }

        return rc;

}

int 
main(int argc, char ** argv)
{
        int o;
        char* server_port = "11212";
        char* server_ip = "127.0.0.1";
        //char *message = "set username 0 0 8 \r\njohn1234\r\n";
        //char *message = "get username\r\n";
	char message[256];
        int sockfd;
        int i, j;

        /* Command line args:
                -p port
                -h host name or IP
        */
        while ((o = getopt (argc, argv, "p:h:m:")) != -1) {
                switch(o){
                case 'p':
                        server_port = optarg;
                        break;
                case 'h':
                        server_ip = optarg;
                        break;
                case 'm':
                        strcpy(message, optarg);
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
        printf("server_ip: %s   port: %s\n", server_ip, server_port);

	for (j = 0; j < 3; j++) {
		memset(message, 0, sizeof(message));
		switch(j) {
		case 0:
		case 2:
			strcpy(message, "get username\r\n");
			break;
		case 1:
			strcpy(message, "set username 0 0 8 \r\njohn1234\r\n");
			break;
		default:
			break;
		}

		for (i = 0; i < 10; i++) {
			sockfd = sh_client(server_ip, server_port);

			client_request(sockfd, message);
        close(sockfd);
		}

	}

        out:
        close(sockfd);

        printf("Done.\n");
        return 0;
}

