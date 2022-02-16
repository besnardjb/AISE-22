#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>

#include <signal.h>
#include <string.h>
#include <stdio.h>

void func(int sig)
{
	printf("SIG %d\n", sig);
	if(sig != SIGUSR1)
	{
		printf("func() (handler)\n");
		abort();
	}
}

int main(int argc, char *argv[])
{
	pid_t pid = getpid();

	int fd = open("map_file.txt", O_RDWR | O_CREAT, 0600);
	if(fd < 0)
	{
		perror("open");
		abort();
	}

	if(ftruncate(fd, 64) < 0)
	{
		perror("ftruncate");
		abort();
	}

	void* p = mmap(NULL, 64, PROT_WRITE, MAP_FILE | MAP_SHARED, fd, 0);
	if(p == MAP_FAILED)
	{
		perror("mmap");
		abort();
	}
	close(fd);

	memcpy(p, &pid, sizeof(pid_t));

	if(signal(SIGUSR1, func) == SIG_ERR)
	{
		printf("Error w/ signal()\n");
		abort();
	}

	printf("Pause: waiting to be killed (PID: %d)\n", (int) pid);
	pause();
	munmap(p, 64);
	return 0;
}
