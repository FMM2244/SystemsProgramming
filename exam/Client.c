#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 



int main(int argc, char *argv[])
{ int sockfd, portno;
   struct sockaddr_in serv_addr;
  // struct hostent *server;
   char buffer[256];
   portno = 1200;
   sockfd = socket(AF_INET, SOCK_STREAM, 0); 
   //server = gethostbyname(argv[1]);
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
//bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
 serv_addr.sin_addr.s_addr = INADDR_ANY;
 serv_addr.sin_port = htons(portno);
 connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
  //senario
 
	int n = 0;
	char buf[10];

	printf("Enter N: ");
    scanf("%d", &n);

	sprintf(buf, "%d", n);
	write(sockfd, buf, sizeof(buf));

	read(sockfd, buf, sizeof(buf));
	printf("%s", buf);

    close(sockfd);
   }
