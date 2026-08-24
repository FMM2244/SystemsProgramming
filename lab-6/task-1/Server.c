#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

// void add(int fd, int x, int y) {
// 	char tmp[200];
// 	sprintf(tmp, "%d + %d = %d", x, y, x + y);
// 	write(fd, tmp, sizeof(tmp));
// }

// void sub(int fd, int x, int y) {
// 	char tmp[200];
// 	sprintf(tmp, "%d - %d = %d", x, y, x - y);
// 	write(fd, tmp, sizeof(tmp));
// }

// void multi(int fd, int x, int y) {
// 	char tmp[200];
// 	sprintf(tmp, "%d * %d = %d", x, y, x * y);
// 	write(fd, tmp, sizeof(tmp));
// }

// void my_div(int fd, int x, int y) {
// 	char tmp[200];
// 	if (y == 0)
// 		sprintf(tmp, "can't be divided");
// 	else
// 		sprintf(tmp, "%d / %d = %d", x, y, x / y);
// 	write(fd, tmp, sizeof(tmp));
// }

int main(int argc, char *argv[]) {

	if (argc != 2)
		return 1;

    srand(time(NULL));

	int sockfd, newsockfd, portno, clilen, n;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port =  htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	
	bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	listen(sockfd,5);
	printf("the server is up and running...\n");
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	
	int target = (rand() % (10 - 3 + 1)) + 3;

	char tmp[100];
	sprintf(tmp, "please enter your guess: ");
	write(newsockfd, tmp, sizeof(tmp));
	while (1) {
		//the senario
		read(newsockfd, tmp, 8);
		size_t i = 0;
		int x = atoi(tmp);
	
		if (x == target) {
			sprintf(tmp, "good job <3");
			write(newsockfd, tmp, sizeof(tmp));
			break ;
		}
		else if (x < target) {
			sprintf(tmp, "Hint (higher)\nplease enter your guess: ");
			write(newsockfd, tmp, sizeof(tmp));
		}
		else {
			sprintf(tmp, "Hint (lower)\nplease enter your guess: ");
			write(newsockfd, tmp, sizeof(tmp));
		}
	}
	close(newsockfd);
	close(sockfd);
}

