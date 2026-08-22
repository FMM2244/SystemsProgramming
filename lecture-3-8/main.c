# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define BUFF_SIZE 5

int main() {

	int pipe1[2];
	int pipe2[2];

	if (pipe(pipe1) == -1)
		return 1;
	if (pipe(pipe2) == -1) {
		close(pipe1[0]);
		close(pipe1[1]);
		return 1;
	}

	pid_t pid = fork();
	if (pid == -1)
		return -1;
	else if (pid == 0) {
		// child
		int arr[BUFF_SIZE] = {4, 5, 6, 8, 2};
		close(pipe1[1]);
		close(pipe2[0]);
		printf("Child: writting numbers to pipe...\n");
		write(pipe2[1], arr, sizeof(arr));
		sleep(2);
		int result[BUFF_SIZE];
		read(pipe1[0], result, sizeof(result));
		for (int i = 0; i < sizeof(result) / sizeof(int); i++) {
			printf("Child: the result is %d\n", result[i]);
		}
		close(pipe1[0]);
		close(pipe2[1]);
	}
	else {
		// parent
		int arr[BUFF_SIZE];
		close(pipe1[0]);
		close(pipe2[1]);
		printf("Parent: reading numbers from pipe...\n");
		read(pipe2[0], arr, sizeof(arr));
		int result[BUFF_SIZE];
		for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
			result[i] = arr[i];
			for (int j = arr[i] - 1; j > 1; j--) {
				result[i] *= j;
			}
		}
		write(pipe1[1], result, sizeof(result));
		wait(NULL);
		close(pipe1[1]);
		close(pipe2[0]);
	}

	return 0;
}