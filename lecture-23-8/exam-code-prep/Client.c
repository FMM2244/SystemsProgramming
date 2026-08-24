#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 



int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	// struct hostent *server;
	char buffer[256];
	portno = 8081;
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	//server = gethostbyname(argv[1]);
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	//bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
	//senario

	int x;
	int y;
	char tmp[200];
	read(sockfd, tmp, 200);
	printf("%s\n", tmp);
	scanf("%d%d", &x, &y);
	sprintf(tmp, "%d,%d", x, y);
	write(sockfd, tmp, strlen(tmp));

	for (int i = 0; i < 4; i++) {
		read(sockfd, tmp, 200);
		printf("%s\n", tmp);
	}

	close(sockfd);
}
