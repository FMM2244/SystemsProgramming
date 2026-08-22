
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>
# include <sys/random.h>

typedef struct player {
	int id;
	int nb_attempts;
	long long start_time;
	long long end_time;
}	player;

typedef struct game {
	int random_number;
	int nb_players;
	player *players;
	
}	game_container;

void playGame(player *p, int target) {
	// srand(0);
	int input;
	
	input = (rand() % (100 - 1 + 1)) + 1;
	p->nb_attempts++;
	while (input != target) {
		usleep(10000);
		input = (rand() % (100 - 1 + 1)) + 1;
		p->nb_attempts++;
	}
	p->end_time = time(NULL);
}

void printResults(game_container *session) {
	int winner_id = session->players[0].id;
	int winner_attempts = session->players[0].nb_attempts;
	printf("Target number: %d\nNo. players: %d\n", session->random_number, session->nb_players);
	printf("---------------------------------------------------------------\n");
	printf("Print results\n");
	printf("---------------------------------------------------------------\n");
	printf("ID\tAttempts\tTime(sec)\n");
	printf("---------------------------------------------------------------\n");
	for (int i = 0; i < session->nb_players; i++) {
		printf("%d\t%d\t%lld\n", session->players[i].id, session->players[i].nb_attempts, session->players[i].end_time - session->players[i].start_time);
		if (session->players[i].nb_attempts < winner_attempts) {
			winner_attempts = session->players[i].nb_attempts;
			winner_id = session->players[i].id;
		}
	}
	printf("---------------------------------------------------------------\n");
	printf("The winner is: %d (Attempts: %d)\n", winner_id, winner_attempts);
}

int main( int ac, char **av ) {
	srand(time(NULL));
	game_container game_session;
	game_session.nb_players = (rand() % (10 - 3 + 1)) + 3;

	game_session.players = malloc(sizeof(player) * game_session.nb_players);
	if (game_session.players == NULL)
		return 1;

	game_session.random_number = (rand() % (100 - 1 + 1)) + 1;
	for (int i = 0; i < game_session.nb_players; i++) {
		game_session.players[i].id = i;
		game_session.players[i].start_time = time(NULL);
		game_session.players[i].nb_attempts = 0;
		playGame(&(game_session.players[i]), game_session.random_number);
	}
	printResults(&game_session);
}
