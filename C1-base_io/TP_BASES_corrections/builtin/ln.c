#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if(argc != 3)
		return 0;


	symlink(argv[1], argv[2]);
	

	return 0;
}
