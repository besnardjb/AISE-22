#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if(argc == 1)
		return 0;


	if( chdir(argv[1]) )
	{
		perror("chdir");
		exit(1);
	}
	

	return 0;
}
