#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i = 0, max = 10, sum = 0;
	printf("Hello, World !\n");

	if(argc >= 2)
		max = atoi(argv[1]);


	for(i=0; i < max; i++)
		sum += i;

	printf("Sum of %d first integers: %d\n", max, sum);
	
	return 0;
}
