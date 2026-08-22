#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct player {
    pthread_mutex_t *print_mutex;
    pthread_t th;
    int id;
    int nb_attempts;
    int target;
    long time;
} player;

typedef struct game {
    int random_number;
    int nb_players;
} game_container;

volatile int g_flag;

void *playGame(void *p) {
    player *plyr = (player *)p;
    int input;
    struct timeval start;
    struct timeval end;
    
    gettimeofday(&start, NULL);
    
    while (1) {
        if (g_flag != -1) {
            return NULL; 
        }

        input = (rand() % (10 - 1 + 1)) + 1;
        plyr->nb_attempts++;

        if (input == plyr->target) {
            pthread_mutex_lock(plyr->print_mutex);
            if (g_flag == -1) {
                g_flag = plyr->id;
                
                gettimeofday(&end, NULL);
                long time_taken = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
                plyr->time = time_taken;
                
                printf("The winner is...\n");
                printf("Player %d finished! Attempts: %d, Time taken: %ld us\n", plyr->id, plyr->nb_attempts, time_taken);
            }
            pthread_mutex_unlock(plyr->print_mutex);
            return NULL;
        }
        
        usleep(10);
    }
    return NULL;
}

int main(int ac, char **av) {
    // initial setup
    srand(time(NULL));
    game_container game_session;
    game_session.nb_players = (rand() % (10 - 3 + 1)) + 3;
    player players[game_session.nb_players];
    game_session.random_number = (rand() % (10 - 1 + 1)) + 1;

    // initial print
    printf("target number: %d\nno. players: %d\n\n", game_session.random_number, game_session.nb_players);
    printf("---------------------------------------------------------------\n");

    // mutexes setup
    players[0].print_mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(players[0].print_mutex, NULL);
    g_flag = -1; // -1 means no one has won yet

    // players setup
    for (int i = 0; i < game_session.nb_players; i++) {
        players[i].id = i;
        players[i].nb_attempts = 0;
        players[i].target = game_session.random_number;
        players[i].print_mutex = players[0].print_mutex;
        if (pthread_create(&players[i].th, NULL, playGame, &players[i]))
            return 1;
    }

    // Wait for all threads to finish
    for (int i = 0; i < game_session.nb_players; i++)
        pthread_join(players[i].th, NULL);

    printf("\n---------------------------------------------------------------\n");

    // Print all players who were stopped
    for (int i = 0; i < game_session.nb_players; i++) {
        if (g_flag != i) {
            printf("Player %d (stopped)\n", players[i].id);
        }
    }

    // Cleanup
    pthread_mutex_destroy(players[0].print_mutex);
    free(players[0].print_mutex);

    return 0;
}