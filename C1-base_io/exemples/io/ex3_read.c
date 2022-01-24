#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char ** argv)
{
	printf("%s\n", argv[0]);

	if( argc != 2 )
	{
		fprintf(stderr, "Usage %s PATH\n", argv[0]);
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);

	if( fd < 0 )
	{
		perror("open");
		return 1;
	}

	int cnt;
	char buff[500];

	while( (cnt = read(fd, buff, 500)) != 0)
	{
		if( cnt < 0)
		{
			perror("read");
			return 1;
		}

		int ret = write(STDOUT_FILENO, buff, cnt);

		if( ret < 0)
		{
			perror("write");
			return 1;
		}
	}


	close(fd);

	return 0;
}



