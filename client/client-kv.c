#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include "../lib/marshal/marshal.h"
/****************************************
 Author: Joel Klein, Katie Stasaski, Lucas Chaufournier, Tim Wood
 with a little help from
 http://beej.us/guide/bgnet/
 ****************************************/
//Returns the number of bytes to wait for

struct operation* read_line(int sockfd)
{
	char curr_char;
	int cont = 1;
	int i;
	char* msg = malloc(1024);
	struct operation** marshal_msg = malloc(sizeof(struct operation));
	int * status;

	//printf("reading lines\n");
	i = 0;
	for(i=0; i<3; i++) {
		while(1) {
			msg[i] = curr_char;
			i++;
			recv(sockfd, &curr_char, 1, 0);
			if(curr_char == ' ') {
				printf(" ");
				break;
			}
			printf("%c",curr_char);

		}
		cont = 1;
	}

	while(1) {
		recv(sockfd, &curr_char, 1, 0);
		if (curr_char == '\r') {
			recv(sockfd, &curr_char, 1, 0);
			if (curr_char == '\n') {
				break;
			}
		} else {
			msg[i] = curr_char;
		}
		i++;
	}
	gwkv_demarshal_client(msg, marshal_msg, status);
	if (*status == -1) {
		return 0;
	} else {
		return *marshal_msg;
	}
}

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
	size_t len = 0;
	char * temp;
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

	if(cmd[0] == 's'){

		memcache_req = malloc(sizeof(cmd) + sizeof(key) + sizeof(num_bytes) + 14);
		num_bytes = strlen(value);
		sprintf(memcache_req, "%s %s 0 0 %d\r\n", cmd, key, num_bytes);
		memcache_req2 = malloc(sizeof(value)+5);
		sprintf(memcache_req2, "%s\r\n", value);
		printf("%s\n",memcache_req);
		printf("%s\n",memcache_req2);
		printf("test1\n");

		struct operation* marshal_msg = malloc(sizeof(struct operation));
		marshal_msg -> method_type = SET;
		marshal_msg -> key = malloc(sizeof(key));
		marshal_msg -> key = key;
		marshal_msg -> key_length = strlen(key);
		marshal_msg -> value = malloc(sizeof(num_bytes));
		marshal_msg -> value = value;
		marshal_msg -> value_length = num_bytes;
        printf("Before Marshal String\n");
		gwkv_marshal_client(marshal_msg, &temp);
        printf("Marshalled string is %s\n",temp);
	}
	else{
		
		memcache_req = malloc(sizeof(cmd) + sizeof(key) + sizeof(num_bytes) + 14);
		struct operation* marshal_msg = malloc(sizeof(struct operation));
		marshal_msg -> method_type = GET;
		marshal_msg -> key = malloc(sizeof(key));
		marshal_msg -> key = key;
		marshal_msg -> key_length = strlen(key);
		gwkv_marshal_client(marshal_msg, &temp);
	
		//memcache_req = malloc(sizeof(cmd) + sizeof(key) +6);
		//sprintf(memcache_req, "%s %s\r\n", cmd, key);
		//printf("%s\n",memcache_req);
	//	printf("testing2\n");
	}
	//printf("server_ip: %s   port: %s\n", server_ip, server_port);

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
	//printf("connected\n");
	if(cmd[0]=='s'){
		/* Sends the http request. */
		rc = send(sockfd,temp,strlen(temp), 0);
		if(rc < 0) {
			perror("ERROR on send");
			exit(-1);
		}

	}
	else{
		rc = send(sockfd,temp,strlen(temp),0);
		if(rc < 0){
			perror("ERROR ON SEND");
			exit(-1);
		}

		struct operation* demarshaled_msg = malloc(sizeof(struct operation));
		demarshaled_msg = read_line(sockfd);

		bytes_received = recv(sockfd, recv_data, demarshaled_msg->value_length, 0);
		printf("%s\n", recv_data);
	}
//default buffer size is 1024.  recv receives the info from the server.
/*	bytes_received = recv(sockfd,recv_data,1024,0);

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
*/
	//closes socket
	out:
		freeaddrinfo(server);
	close(sockfd);

	//printf("Done.\n");
	return 0;

}
