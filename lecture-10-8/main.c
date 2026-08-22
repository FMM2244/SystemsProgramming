
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>

int main() {
	int fd1;
	char c1, c2;
	fd1 = open("test", O_RDONLY, 0);
	if (fork()) {
		// parent
		read(fd1, &c1, 1);
		printf("%c", c1);
		// while (read(fd1, &c1, 1))
		// 	printf("%c", c1);

	}
	else {
		// child
		read(fd1, &c1, 1);
		printf("%c", c1);
		// while (read(fd1, &c1, 1))
		// 	printf("%c", c1);
	}
	close(fd1);
	return 0;
}
