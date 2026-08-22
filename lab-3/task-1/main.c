
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>
# include <string.h>
# include <sys/random.h>

typedef struct player {
	int id;
	int nb_attempts;
}	player;

typedef struct game {
	int random_number;
	int nb_players;
	int *pipes_fds;
	int *attempts_res;
	long *time_res;
}	game_container;

void playGame(player *p, int target , int fds[2]) {
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
	dprintf(fds[1], "%d\n%ld", p->nb_attempts, time_taken);
}

void clean_up(game_container gs) {
	for (int i = 0; gs.nb_players * 2; i++) {
		if (gs.pipes_fds[i] != -1) {
			close(gs.pipes_fds[i]);
			gs.pipes_fds[i] = -1;
		}
	}
	free(gs.pipes_fds);
}

int main( int ac, char **av ) {
	// initial setup
	srand(time(NULL));
	game_container game_session;
	game_session.nb_players = (rand() % (10 - 3 + 1)) + 3;
	player players[game_session.nb_players];
	game_session.random_number = (rand() % (100 - 1 + 1)) + 1;
	game_session.pipes_fds = malloc(sizeof(int) * game_session.nb_players * 2);
	game_session.attempts_res = malloc(sizeof(int) * game_session.nb_players);
	game_session.time_res = malloc(sizeof(long) * game_session.nb_players);
	int tmp_arr[2];

	for (int i = 0; i < game_session.nb_players * 2; i++) {
		game_session.pipes_fds[i] = -1;
	}

	// initial print
	printf("target number: %d\nno. players: %d\n\n", game_session.random_number, game_session.nb_players);
	printf("---------------------------------------------------------------\n");

	// players and pipes setup
	for (int i = 0; i < game_session.nb_players; i++) {
		if (pipe(tmp_arr) == -1) {
			for (int j = 0; j < i; j++) {
				wait(NULL);
			}
			clean_up(game_session);
			return 1;
		}
		game_session.pipes_fds[i * 2] = tmp_arr[0];
		game_session.pipes_fds[i * 2 + 1] = tmp_arr[1];
		pid_t pid = fork();
		if (pid == -1) {
			for (int j = 0; j < i; j++) {
				wait(NULL);
			}
			clean_up(game_session);
			return 1;
		}
		players[i].id = i;
		players[i].nb_attempts = 0;
		if (pid == 0) {
			playGame(&(players[i]), game_session.random_number, tmp_arr);
			// clean_up(game_session);
			exit(0);
		}
	}

	// read data
	char buf[31];
	int j = 0;
	for (int i = 0; i < game_session.nb_players * 2; i += 2) {
		int ret = read(game_session.pipes_fds[i], buf, sizeof(buf) - 1);
		if (ret > 0) {
			buf[ret] = '\0';
			sscanf(buf, "%d\n%ld", &game_session.attempts_res[j], &game_session.time_res[j]);
			printf("\n---------------------------------------------------------------\n");
			printf("Player id: %d\nNo. attempts: %d\nTime taken: %ld\n", 
					players[j].id, game_session.attempts_res[j], game_session.time_res[j]);
		}
		j++;
	}

	// determine winner
	int winner_id = 0;
	for (int i = 1; i < game_session.nb_players; i++) {
		if (game_session.attempts_res[i] < game_session.attempts_res[winner_id])
			winner_id = i;
		else if (game_session.attempts_res[i] == game_session.attempts_res[winner_id] && game_session.time_res[i] < game_session.time_res[winner_id])
			winner_id = i;
	}
	printf("\n---------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("The winner is:\n");
	printf("Player id: %d, (attempts: %d), (time taken: %ld)\n", winner_id, game_session.attempts_res[winner_id], game_session.time_res[winner_id]);

	// wait loop
	for (int j = 0; j < game_session.nb_players; j++)
		wait(NULL);

	// final clean up
	// clean_up(game_session);
	return 0;
}
