
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    int pipe1[2];
    int pipe2[2];
    if (pipe(pipe1) == -1) {
        printf("An error ocurred with opening the pipe1\n");
        return 1;   }
	if (pipe(pipe2) == -1) {
        printf("An error ocurred with opening the pipe2\n");
        return 1;
	}

    int id = fork();
    if (id == -1) {
        printf("An error ocurred with fork\n");
		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe2[1]);
        return 2;
	}

    // if (id == 0) {
    //     // Child process
    //     close(fd[0]);
    //     int x;
    //     printf("Input a number: ");
    //     scanf("%d", &x);
    //     if (write(fd[1], &x, sizeof(int)) == -1) {
    //         printf("An error ocurred with writing to the pipe\n");
    //         return 3; }
    //     close(fd[1]);
    // } else {
    //     // Parent process
    //     close(fd[1]);
    //     int y;
    //     if (read(fd[0], &y, sizeof(int)) == -1) {
    //         printf("An error ocurred with reading from the pipe\n");
    //         return 4;
    //     }
    //     printf("Got from child process %d\n", y);
    //     y = y * 3;
    //     printf("Result is %d\n", y);
    //     close(fd[0]);
    // }

    return 0;
}