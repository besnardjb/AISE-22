#include <pthread.h>
#include <stdio.h>

__thread int global;

void * func(void*arg)
{
	printf("global = %d //// %p\n", global, &global);
}

int main(int argc, char *argv[])
{
	pthread_t pid[2];
	int i = 0;

	for (i = 0; i < 2; ++i) {
		pthread_create(pid+i, NULL, func, NULL);
	}

	for (i = 0; i < 2; ++i) {
		pthread_join(pid[i], NULL);
	}

	
	return 0;
}
