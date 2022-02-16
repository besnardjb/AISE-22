#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/mman.h>
#include <string.h>

size_t square(int n)
{
	return n * n;
}
void end_square() {}

int main(int argc, char *argv[])
{
	int fd = open("libsquare.o", O_RDWR | O_CREAT, 0600);
	if(fd < 0)
	{
		perror("open");
	}

	size_t size = (char*)end_square - (char*)square;
	if(ftruncate(fd, size) <0)
		perror("ftruncate");


	void *p = mmap(NULL, size, PROT_WRITE, MAP_SHARED | MAP_FILE, fd, 0);
	if(p == MAP_FAILED)
		perror("mmap");

	memcpy(p, (void*)square, size);
	munmap(p, size);
	close(fd);

	return 0;
}
