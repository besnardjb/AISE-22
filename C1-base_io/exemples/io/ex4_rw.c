#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

ssize_t safe_write(int fd, void *buff,  size_t size)
{
	size_t written = 0;
	while( (size - written) != 0 )
	{
		errno = 0;
		ssize_t ret = write(fd, buff + written, size-written);

		if( ret < 0 )
		{
			if(errno == EINTR)
			{
				continue;
			}

			perror("write");
			return ret;
		}

		written += ret;
	}

	return 0;
}	



int main(int argc, char ** argv){

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

	ssize_t cnt;
	char buff[500];

	while( (cnt = read(fd, buff, 500)) != 0)
	{
		if( cnt < 0)
		{
			perror("read");
			return 1;
		}

		int ret = safe_write(STDOUT_FILENO, buff, cnt);

		if( ret < 0)
		{
			perror("write");
			return 1;
		}
	}


	close(fd);

	return 0;
}



