#include <stdio.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

pid_t child = 0;

int cnt_pipe = 0;
int cnt_cont = 0;

void sigchild(int sig)
{
	switch(sig)
	{
		case SIGCONT:
			printf("GOT sigcont %d\n", sig);
			cnt_cont++;
			break;
		case SIGPIPE:
			printf("GOT sigpipe %d\n", sig);
			cnt_pipe++;
			break;
		default:
			printf("WHUUUT ?\n");
	}
}

void sigprint(int sig)
{
	printf("Child got SIGPIPE %d times SICONT %d times\n", cnt_pipe, cnt_cont);
	exit(0);
}


int main(int argc, char ** argv)
{
	child = fork();

	if(child == 0)
	{
		signal(SIGCONT, sigchild);
		signal(SIGPIPE, sigchild);
		signal(SIGINT, sigprint);

		while(1){}
	}
	else
	{
		int i;

		for(i = 0 ; i < 30 ; i++)
		{
			if(rand()%2)
			{
				kill(child, SIGCONT);
			}
			else
			{
				kill(child, SIGPIPE);
			}
			sleep(1);
		}

		kill(child, SIGINT);
		wait(NULL);
	}




	return 0;
}


