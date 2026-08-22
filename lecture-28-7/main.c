# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int main( int ac, char **av ) {
	char *cmd = "cat";
	char *cmd_args[4] = {cmd, "-e", "text", NULL};

	printf("HELLO\n");
	for (int i = 1; i < ac; i++)
		printf("\t%s\n", av[i]);
	return 0;
}
