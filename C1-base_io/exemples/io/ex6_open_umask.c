#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	umask(0000);
	int fd = open("./toto_um", O_RDWR | O_CREAT, 0777 );

	if( fd < 0)
	{
		perror("open");
	}


	close(fd);

	return 0;
}

