#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char ** argv )
{
	int val = 2;
	pid_t child = fork();

	if( child == 0 )
	{
		val++;
	} else {
		val+=2;
		wait(NULL);
	}

	fprintf(stderr, "PID %d PPID %d VAL is %d\n",
			getpid(),
			getppid(),
			val);

	return 0;
}
