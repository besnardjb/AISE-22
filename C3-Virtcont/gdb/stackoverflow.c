#include <signal.h>
#include <stdio.h>
#include <execinfo.h>
#include <stdlib.h>
#include <unistd.h>


void foo(int b);


void sigh(int sig)
{

	printf("J'ai planté :'(\n");

	void * addrs[64];
	int cnt = backtrace((void**)&addrs, 64);

	int i;

	for(i = 0; i < cnt; i++)
	{
		printf("%d == %p\n", i, addrs[i]);
	}

       //backtrace_symbols_fd(addrs, cnt, STDOUT_FILENO);
       //libunwind

	exit(1);
}



int main(int argc, char ** argv)
{
	signal(SIGSEGV, sigh);

	char * buff = malloc(512);



	return 0;
}
