#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char ** argv )
{
	pid_t child = fork();

	if( child == 0)
	{
		int out = open("./out.dat", O_CREAT | O_WRONLY | O_APPEND , 0600);
		/* Replace stdout with the file */
		dup2(out, STDOUT_FILENO);
		close(out);
		char * argv[] = {"cowsay","COUCOU POSIX", NULL};
		execvp( argv[0], argv);
	}
	else
	{
		/* Parent closes out */
		wait(NULL);
	}


	return 0;
}

