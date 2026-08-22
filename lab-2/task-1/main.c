
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>
# include <sys/random.h>

typedef struct player {
	int id;
	int nb_attempts;
}	player;

typedef struct game {
	int random_number;
	int nb_players;
}	game_container;

void playGame(player *p, int target) {
	int input;
	struct timeval start;
	struct timeval end;
	
	gettimeofday(&start, NULL);
	input = (rand() % (100 - 1 + 1)) + 1;
	p->nb_attempts++;
	while (input != target) {
		usleep(100000);
		input = (rand() % (100 - 1 + 1)) + 1;
		p->nb_attempts++;
	}
	gettimeofday(&end, NULL);
	printf("Print results for player %d\n", p->id);
	printf("---------------------------------------------------------------\n");
	printf("child pid: %d\nno. attempts: %d\ntime taken: %ld\n\n", getpid(), p->nb_attempts, (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000);
}

int main( int ac, char **av ) {
	srand(time(NULL));
	game_container game_session;
	game_session.nb_players = (rand() % (10 - 3 + 1)) + 3;
	player players[game_session.nb_players];
	game_session.random_number = (rand() % (100 - 1 + 1)) + 1;

	printf("target number: %d\nno. players: %d\n\n", game_session.random_number, game_session.nb_players);
	printf("---------------------------------------------------------------\n");
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
			playGame(&(players[i]), game_session.random_number);
			exit(0);
		}
	}
	for (int j = 0; j < game_session.nb_players; j++)
		wait(NULL);
}
