#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>

/****************************************
 Author: Joel Klein, Katie Stasaski, Lucas Chaufournier, Tim Wood
 with a little help from
 http://beej.us/guide/bgnet/
 ****************************************/

int main(int argc, char ** argv)
{
	//port used to connect to socket
	char* server_port = "80";
	//ip address or host name of server http request will be sent to
	char* server_ip = "google.com";
	//socket int used to connect
	int sockfd, rc;
	//used to store formatted http request
	char * memcache_req; 
	struct addrinfo hints, *server;
	char *message = "";
	//bytes received from server
	int bytes_received = -1;
	//data received from http request--will be printed out to user
	char * recv_data = (char *)malloc(sizeof(char*)*1000);
	int o;
	char * cmd;
	char * key;
	char * value;
	int num_bytes;
	char * memcache_req2;	
        /* Command line args:
                -p port
                -h host name or IP
		-m message (specific page you are requesting.  For ex, when
		   requesting www.cs.gwu.edu/research, the message would be
		   research.)
        */
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
	
	num_bytes = sizeof(value);
	memcache_req = malloc(sizeof(cmd) + sizeof(key) + sizeof(num_bytes) + 14);
	sprintf(memcache_req, "%s %s 0 0 %d 0 \r\n", cmd, key, num_bytes);
	memcache_req2 = malloc(sizeof(value)+5);
	sprintf(memcache_req2, "%s\r\n", value);	
	sockfd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);

	if (sockfd == -1) {
		perror("ERROR opening socket");
		exit(-1);
	}

	rc = connect(sockfd, server->ai_addr, server->ai_addrlen);
	if (rc == -1) {
		perror("ERROR on connect");
		close(sockfd);
		exit(-1);
		// TODO: could use goto here for error cleanup
	}

	/* Sends the http request. */
	rc = send(sockfd,memcache_req,strlen(memcache_req), 0);
	if(rc < 0) {
		perror("ERROR on send");
		exit(-1);
	}
	rc = send(sockfd, memcache_req2,strlen(memcache_req2),0);
	if(rc < 0){
		perror("ERROR on send 2nd msg");
		exit(01);
	}
	//default buffer size is 1024.  recv receives the info from the server.
	bytes_received = recv(sockfd,recv_data,1024,0);

	while(bytes_received)
	{
		//default buffer size is 1024
		bytes_received = recv(sockfd,recv_data,1024,0);

		if(bytes_received == -1)
		{
			perror("recv");
			exit(1);
		}

		//prints out information to user
		printf("%s\n",recv_data);
		if(bytes_received==0){ 
			break; 
		}
		recv_data[bytes_received] = '\0';
	}

	//closes socket
	out:
		freeaddrinfo(server);
	close(sockfd);

	printf("Done.\n");
	return 0;

}

