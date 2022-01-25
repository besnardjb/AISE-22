#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv, char ** envp)
{
	int i;

	while(*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}

	printf("LOL = %s\n", getenv("LOL"));
	
	return 0;
}
