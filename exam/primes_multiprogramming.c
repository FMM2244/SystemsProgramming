#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int isPrime(int n)
{
    if (n < 2)
        return 0;

    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return 0;

    return 1;
}

int main()
{
    int N, count = 0;

    printf("Enter N: ");
    scanf("%d", &N);

    printf("The Primes are:\n");
	
    	for (int i = 2; i <= N; i++) {
	    	int pid = fork();
	    	if (pid == 0) {
		    	if (isPrime(i)) {
			    printf("%d ", i);
			    // count++;
			}
		    exit(0);
		}
	}
	for (int i = 2; i <= N; i++) {
                wait(NULL);
	}

    printf("\n");

    // printf("Number of primes = %d\n", count);

    return 0;
}
