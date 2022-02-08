#include <stdlib.h>
#include <stdio.h>

#define NB 1024

int main(int argc, char *argv[])
{
	int** array = NULL;
	int i;
	int sum = 0;

	array = (int**)malloc(sizeof(int*) * NB);

	for (i = 0; i < NB; ++i) {
			sum += i;
			array[i] = malloc(sizeof(int));
			*(array[i]) = sum;
			printf("Sum from [0-%d] = %d\n", i, sum );
		}

	for (i = 0; i < NB; ++i) {
			free(array[i]);
		}

	free(array);
	
	return 0;
}
