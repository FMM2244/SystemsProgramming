
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/random.h>

typedef struct player {
	int id;
	int nb_attempts;
}	player;

typedef struct game {
	int random_number;
	int nb_players;
}	game_container;

void playGame(player *p, int target , int fd) {
	int input;
	struct timeval start;
	struct timeval end;
	
	gettimeofday(&start, NULL);
	input = (rand() % (100 - 1 + 1)) + 1;
	p->nb_attempts++;
	while (input != target) {
		usleep(1000000);
		input = (rand() % (100 - 1 + 1)) + 1;
		p->nb_attempts++;
	}
	gettimeofday(&end, NULL);
	long time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000;

	// write result to parent
	char *tmp;
	sprintf(tmp, "player %d | attempts %d | time taken %ld\n", p->id ,p->nb_attempts, time_taken);
	printf("%s", tmp);
	lseek(fd, 0, SEEK_END);
	write(fd, tmp, strlen(tmp));
	// dprintf(fd, "%d\n%ld", p->nb_attempts, time_taken);
}

int main( int ac, char **av ) {
	// initial setup
	srand(time(NULL));
	game_container game_session;
	game_session.nb_players = (rand() % (10 - 3 + 1)) + 3;
	player players[game_session.nb_players];
	game_session.random_number = (rand() % (100 - 1 + 1)) + 1;

	int fd = open("players_results.csv", O_RDWR | O_CREAT | O_APPEND, 0664);
	if (fd == -1) {
		printf("Can't open data file\nTry again later...\n");
		return 1;
	}

	// initial print
	printf("target number: %d\nno. players: %d\n\n", game_session.random_number, game_session.nb_players);
	printf("---------------------------------------------------------------\n");

	// players setup
	for (int i = 0; i < game_session.nb_players; i++) {
		pid_t pid = fork();
		if (pid == -1) {
			for (int j = 0; j < i; j++) {
				wait(NULL);
			}
			return 1;
		}
		players[i].id = i;
		players[i].nb_attempts = 0;
		if (pid == 0) {
			playGame(&(players[i]), game_session.random_number, fd);
			exit(0);
		}
	}

	// wait loop
	for (int j = 0; j < game_session.nb_players; j++)
		wait(NULL);

	int n = 0;
	char *buf;
	while ((n = read(fd, buf, 20)) != 0) {
		printf("%s", buf);
	}

	close(fd);
	// free();
	return 0;
}
