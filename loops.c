
# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>

int main(int ac, char **av) {
	DIR *dir;
	struct dirent *entry;

	dir = opendir(".");

	while ((entry = readdir(dir)) != NULL)
	{
		if (strstr(entry->d_name, ".log") != NULL)
		{
			printf("Processing %s\n", entry->d_name);
			/* Open and process the file */
		}
	}

	closedir(dir);
}