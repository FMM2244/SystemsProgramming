//https://tf.nist.gov/tf-cgi/servers.cgi
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <errno.h>
#include <arpa/inet.h>

int main(int args,char * argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[1024]={0};
	char * IP;
	//Step1: create the client socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//Step2: get the ip address of the sever
	server = gethostbyname(argv[1]);
	//serv_addr.sin_addr.s_addr=INADDR_ANY;

	IP = inet_ntoa(*((struct in_addr*) server->h_addr_list[0]));
	printf("the socket returns %s: %s %d\n",server->h_name,IP,sockfd);

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

	bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port = htons(atoi(argv[2]));
	//Step3 : connect to server
	connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

	// bzero(buffer,1024);
	// write(sockfd,"hello",5);
	n = read(sockfd,buffer,1024);
	printf("the time is %s\n", buffer);
	printf("the time is %d\n", n);
	close(sockfd);
	return 0;
}
