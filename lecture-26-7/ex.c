# include <unistd.h>
# include <stdio.h>

int main() {
	printf("the pid of the process: %d\n", (int)getpid());
	printf("the pid of the parent process: %d\n", (int)getppid());
	return 0;
}
