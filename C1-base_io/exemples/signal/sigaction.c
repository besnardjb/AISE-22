#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void  plop(int sig,
	   siginfo_t *info,
	   void *ctx)
{
	printf("SIGNINT :'(\n");
}


int main(int argc, char ** argv)

{
	struct sigaction act;

	memset(&act, 0, sizeof(struct sigaction));

	act.sa_sigaction = plop;
	act.sa_flags = SA_SIGINFO;

	if( sigaction(SIGINT, &act, NULL) )
	{
		perror("sigaction");
		return 1;
	}


	while(1)
	{
		sleep(1);
	}


	return 0;
}
