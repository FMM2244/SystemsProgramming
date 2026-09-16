#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>



int isPrime(int n)
{
    if (n < 2)
        return 0;

    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return 0;

    return 1;
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno, clilen;
	pthread_t th;
	struct sockaddr_in serv_addr, cli_addr;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	portno = 1200;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port =  htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	
	bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	printf("Echo Server is ON...\n");
	
   	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	//the senario
	int n = 0;
	char buf[100];

	read(newsockfd, buf, sizeof(buf));
	n = atoi(buf);
	if (isPrime(n)) {
		sprintf(buf, "Prime\n");
	}
	else {
		sprintf(buf, "Not Prime\n");
	}
	write(newsockfd, buf, sizeof(buf));
	close(newsockfd);
	close(sockfd);

 }

