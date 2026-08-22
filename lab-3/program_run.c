# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int main( int ac, char **av ) {
	printf("\n\n ================= RUN TASK 1 =================\n\n");
	system("gcc ./task-1/main.c");
	system("./a.out");
	
	printf("\n\n ================= RUN TASK 2 =================\n\n");
	system("gcc ./task-2/main.c");
	system("./a.out");

	return 0;
}
