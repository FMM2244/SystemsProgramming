
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/random.h>
# include <pthread.h>

typedef struct player {
	pthread_mutex_t *print_mutex;
	pthread_mutex_t *arr_mutex;
	pthread_t th;
	int id;
	int nb_attempts;
	int target;
	long time;
}	player;

typedef struct game {
	int random_number;
	int nb_players;
}	game_container;

player *res;
int idx;

void *playGame(void *p) {
	player *plyr = (player *)p;
	int input;
	struct timeval start;
	struct timeval end;
	
	gettimeofday(&start, NULL);
	input = (rand() % (100 - 1 + 1)) + 1;
	plyr->nb_attempts++;
	while (input != plyr->target) {
		usleep(10);
		input = (rand() % (10 - 1 + 1)) + 1;
		plyr->nb_attempts++;
	}
	gettimeofday(&end, NULL);
	long time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000;
	plyr->time = time_taken;
	pthread_mutex_lock(plyr->print_mutex);
	printf("Player %d finished! Attempts: %d, Time taken: %ld\n", plyr->id, plyr->nb_attempts, time_taken);
	pthread_mutex_unlock(plyr->print_mutex);

	pthread_mutex_lock(plyr->arr_mutex);
	res[idx] = *plyr;
	idx++;
	pthread_mutex_unlock(plyr->arr_mutex);
}

int main( int ac, char **av ) {
	// initial setup
	srand(time(NULL));
	game_container game_session;
	game_session.nb_players = (rand() % (10 - 3 + 1)) + 3;
	player players[game_session.nb_players];
	game_session.random_number = (rand() % (10 - 1 + 1)) + 1;

	idx = 0;
	res = malloc(sizeof(player) * (game_session.nb_players + 1));

	// initial print
	printf("target number: %d\nno. players: %d\n\n", game_session.random_number, game_session.nb_players);
	printf("---------------------------------------------------------------\n");

	// mutexes setup
	players[0].print_mutex = malloc(sizeof(pthread_mutex_t));
	players[0].arr_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(players[0].print_mutex, NULL);
	pthread_mutex_init(players[0].arr_mutex, NULL);

	// players setup
	for (int i = 0; i < game_session.nb_players; i++) {
		players[i].id = i;
		players[i].nb_attempts = 0;
		players[i].target = game_session.random_number;
		players[i].print_mutex = players[0].print_mutex;
		players[i].arr_mutex = players[0].arr_mutex;
		if (pthread_create(&players[i].th, NULL, playGame, &players[i]))
			return 1;
	}

	for (int i = 0; i < game_session.nb_players; i++)
		pthread_join(players[i].th, NULL);

	printf("\n---------------------------------------------------------------\n");

	for (int i = 0; i < game_session.nb_players; i++)
		printf("Position %d: Player %d | Attempts: %d | Time taken: %ld\n", i + 1, res[i].id, res[i].nb_attempts, res[i].time);

	return 0;
}
