
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>

int main() {
	int fd1;
	char c1, c2;
	fd1 = open("test", O_RDONLY, 0);
	off_t curr = lseek(fd1, 0, SEEK_CUR);
	if (fork()) {
		// parent
		// read(fd2, &c1, 1);
		// printf("parent %c", c1);
		off_t offset;
		while (read(fd1, &c1, 1)) {
			if ((offset = lseek(fd1, 0, SEEK_CUR)) - curr > 1) {
				curr = lseek(fd1, -1, SEEK_CUR);
				read(fd1, &c1, 1);
			}
			printf("parent %c", c1);
			curr = lseek(fd1, 0, SEEK_CUR);
		}
	}
	else {
		// child
		// read(fd1, &c1, 1);
		// printf("child %c", c1);
		// while (read(fd1, &c1, 1))
		// 	printf("child %c", c1);
		off_t offset;
		while (read(fd1, &c1, 1)) {
			if ((offset = lseek(fd1, 0, SEEK_CUR)) - curr > 1) {
				curr = lseek(fd1, -1, SEEK_CUR);
				read(fd1, &c1, 1);
			}
			printf("child %c", c1);
			curr = lseek(fd1, 0, SEEK_CUR);
		}
	}
	close(fd1);
	return 0;
}
