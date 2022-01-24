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
	return 0;
}
