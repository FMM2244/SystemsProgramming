#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv) {

    char *ip = "192.168.1.117"; // this is used if you need to connect to a specific IP which should be passed to inet_addr(ip) 
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int port = atoi(argv[1]);
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket error");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sock,
                (struct sockaddr*)&server_addr,
                sizeof(server_addr)) < 0) {
        perror("Connection error");
        exit(1);
    }

    printf("Connected to server.\n");
    fflush(stdout);

    while (1) {
        bzero(buffer, BUFFER_SIZE);

        int n = read(sock, buffer, BUFFER_SIZE - 1);
        if (n <= 0) {
            printf("\nServer disconnected.\n");
            fflush(stdout);
            break;
        }

        buffer[n] = '\0';

        /* Print server message immediately */
        printf("%s", buffer);
        fflush(stdout);

        /* Termination conditions */
        if (strstr(buffer, "WIN") ||
            strstr(buffer, "Game Over")) {
            break;
        }

        /* If server expects input (Guess or Name) */
        if (strstr(buffer, "name") ||
            strstr(buffer, "Guess")) {

            bzero(buffer, BUFFER_SIZE);
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';

            write(sock, buffer, strlen(buffer));
        }
    }

    close(sock);
    printf("\nClient terminated.\n");
    return 0;
}

