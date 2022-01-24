#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int fd = open("./toto", O_RDWR | O_CREAT,
		         	S_IRUSR | S_IWUSR );

	if( fd < 0)
	{
		printf("%d == %d\n", errno, EACCES);
		perror("open");
	}


	close(fd);

	return 0;
}
