#include <stdio.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

pid_t child = 0;


void sig_handler(int sig)
{
	printf("Send USR1 to child\n");
	kill(child, 10);
	alarm(3);
}

void sigint(int sig)
{
	printf("Send SIGINT to child\n");
	kill(child, 2);
	exit(1);
}

int cnt = 0;

void sigchild(int sig)
{
	printf("Child got SIGUSR1 %d times\n", ++cnt);
}

int main(int argc, char ** argv)
{
	child = fork();

	if(child == 0)
	{
		signal(SIGUSR1, sigchild);
		while(1){}
	}
	else
	{
		signal(SIGALRM, sig_handler);
		signal(SIGINT, sigint);
		alarm(3);
		wait(NULL);
	}




	return 0;
}


