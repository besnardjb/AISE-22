#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int fd = open("./toto.exo3", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if(fd < 0)
		perror("open");

	if(dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
	
	int i;
	for (i = 0; i < 4096; ++i) {
		printf("%d\n",  i);
	}
	return 0;
}
