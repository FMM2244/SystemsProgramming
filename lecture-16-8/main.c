# include <stdio.h>
# include <pthread.h>

int arr[10];

void *odd_even(void * f) {
	int flag = *((int *)f);
	int *res;
	*res = 0;
	if (flag == 1){
		for (int i = 0; i < 10; i++)
			if (arr[i] % 2)
				(*res)++;
		printf("the no. odds is: %d", *res);
		return (void *)res;
	}
	else if (flag == 0) {
		for (int i = 0; i < 10; i++)
			if (arr[i] % 2 == 1)
				(*res)++;
		printf("the no. evens is: %d", *res);
		return (void *)res;
	}
}

int main() {
	pthread_t thrds[2];
	for (int i = 0; i < 10; i++)
		arr[i] = i;
	pthread_t th1;
	pthread_t th2;
	void **ret1;
	void **ret2;
	if (pthread_create(&th1, NULL, odd_even, (void *)(1)))
		return 1;
	if (pthread_create(&th2, NULL, odd_even, (void *)(0))) {
		pthread_join(th1, ret1);
		return 1;
	}
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	return 0;
}
