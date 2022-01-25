#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


int main(int argc, char ** argv)
{
	if(argc != 3)
	{
		printf("%s [PID] [SIG]\n", argv[0]);
		return 1;
	}

	int pid = atoi(argv[1]);
	int sig = atoi(argv[2]);


	if(kill(pid, sig))
	{
		perror("kill");
		return 1;
	}

	return 0;
}
