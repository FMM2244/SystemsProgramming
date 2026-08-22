# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int main() {
	// this code is a demo for the difference between exec functions and system function

	char *cmd = "ls";
	char *cmd_args[3] = {
		"ls",
		"-la",
		NULL
	};

	// // system()
	// printf("\ncalling system() system call\n\n");
	// system("ls -la");

	// // execvp
	// printf("\ncalling execvp() system call\n\n");
	// execvp(cmd, cmd_args);

	// printf("will this statement be printed????\n");

	// calling my own program
	char *args[5] = {"my-exec", "fatima", "dua", "leen", NULL};
	execvp("./my-exec", args);
	// execv("my-exec", args);
}