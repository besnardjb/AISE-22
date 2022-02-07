#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{

	int pp[2];

	pipe(pp);

	//pp[1] --> pp[0]
	//
	int pid = fork();

	if(pid == 0)
	{
		dup2(pp[1], STDOUT_FILENO);
		close(pp[1]);
		close(pp[0]);

		char *argv[] = {"echo", "8+4", NULL};
		if(execvp(argv[0], argv) == -1)
			perror("echo");
	}
	else
	{


		dup2(pp[0], STDIN_FILENO);
		close(pp[0]);
		close(pp[1]);
		char *argv[] = {"bc", NULL};
		if(execvp(argv[0], argv) == -1)
			perror("bc");
	}
	
	return 0;
}
