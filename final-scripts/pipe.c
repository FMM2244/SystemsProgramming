
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/random.h>

int main(int ac, char **av) {
	int fd[2];
	pid_t pid;

	pipe(fd);

	pid = fork();

	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);

		execlp(av[1], av[1], av[2], NULL);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);

		execlp(av[3], av[3], av[4], NULL);
	}
}