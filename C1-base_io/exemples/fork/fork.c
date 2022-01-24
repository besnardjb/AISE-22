#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char ** argv )
{
	pid_t child = fork();

	if( child == 0 )
	{
		fprintf(stderr, "CHILD\n");
		sleep(5);
		fprintf(stderr, "CHILD: done waiting\n");
	} else {
		fprintf(stderr, "PARENT\n");
		wait(NULL);
		fprintf(stderr, "PARENT: child done\n");
	}

	return 0;
}
