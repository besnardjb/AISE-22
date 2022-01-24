#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char ** argv )
{
	pid_t child = fork();

	if( child == 0 )
	{
		char * const eargv[] = {"ls", "-la", NULL };
		execvp(eargv[0], eargv);
	} else {
		wait(NULL);
		fprintf(stderr, "PARENT: child done\n");
	}

	return 0;
}
