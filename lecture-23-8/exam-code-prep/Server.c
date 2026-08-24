#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void add(int fd, int x, int y) {
	char tmp[200];
	sprintf(tmp, "%d + %d = %d", x, y, x + y);
	write(fd, tmp, sizeof(tmp));
}

void sub(int fd, int x, int y) {
	char tmp[200];
	sprintf(tmp, "%d - %d = %d", x, y, x - y);
	write(fd, tmp, sizeof(tmp));
}

void multi(int fd, int x, int y) {
	char tmp[200];
	sprintf(tmp, "%d * %d = %d", x, y, x * y);
	write(fd, tmp, sizeof(tmp));
}

void my_div(int fd, int x, int y) {
	char tmp[200];
	if (y == 0)
		sprintf(tmp, "can't be divided");
	else
		sprintf(tmp, "%d / %d = %d", x, y, x / y);
	write(fd, tmp, sizeof(tmp));
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno, clilen, n;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	portno = 8081;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port =  htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	
	bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	listen(sockfd,5);
	printf("the server is up and running...\n");
	while (1)
	{
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		//the senario
		char tmp[100];
		sprintf(tmp, "Welcome to the calc server, please enter 2 integers...");
		write(newsockfd, tmp, sizeof(tmp));
		read(newsockfd, tmp, 8);
		size_t i = 0;
		int x = atoi(tmp);
		for (; tmp[i] != ','; i++);
		int y = atoi(tmp + i + 1);
		printf("%d, %d\n", x, y);
	
		add(newsockfd, x, y);
		sub(newsockfd, x, y);
		multi(newsockfd, x, y);
		my_div(newsockfd, x, y);
	}
	close(newsockfd);
	close(sockfd);
}

