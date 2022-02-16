#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	int fd = open("map_file.txt", O_RDONLY, 0600);
	if(fd < 0)
	{
		perror("open");
		abort();
	}

	void *p = mmap(NULL, 64, PROT_READ, MAP_FILE | MAP_SHARED, fd, 0);
	if(p == MAP_FAILED)
	{
		perror("mmap");
		abort();
	}
	close(fd);

	int pid = -1;
	memcpy(&pid, p, sizeof(pid_t));

	printf("Killing PID %d\n", (int) pid);
	kill(pid, SIGUSR1);
	munmap(p, 64);
	return 0;
}
