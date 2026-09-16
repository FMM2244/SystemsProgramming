#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
# include <time.h>
# include <pthread.h>

pthread_mutex_t m;
int count = 0;

int isPrime(int n)
{
    if (n < 2)
        return 0;

    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return 0;

    return 1;
}

void *routine( void * n ) {
	int i = *(int *)n;
	if (isPrime(i)) {
		printf("%d ", i);
		pthread_mutex_lock(&m);
		count++;
		pthread_mutex_unlock(&m);
	}
}

int main()
{
    int N;

    printf("Enter N: ");
    scanf("%d", &N);

    printf("The Primes are:\n");
	pthread_mutex_t m;
	pthread_mutex_init(&m, NULL);
    	pthread_t th[N - 2];
    	for (int i = 0; i <= N - 2; i++) {
	    	int tmp = i + 2;
		pthread_create(&th[i], NULL, routine, &tmp);
		sleep(0.1);
	}
	for (int i = 0; i <= N - 2; i++) {
                pthread_join(th[i], NULL);
	}

    printf("\n");

    printf("Number of primes = %d\n", count);

    return 0;
}
