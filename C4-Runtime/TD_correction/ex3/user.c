#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, char *argv[])
{
	
	int fd = open("libsquare.o", O_RDONLY, 0600);
	if(fd < 0)
	{
		perror("open");
	}


	void * p = mmap(NULL, 4096, PROT_EXEC, MAP_FILE | MAP_SHARED, fd, 0);

	size_t (*func)(int) = NULL;
	func = (size_t(*)(int))p;

	printf("square of %d is %lu\n", 10, func(10) );
	return 0;

}

