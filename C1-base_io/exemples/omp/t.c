#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <omp.h>
	pid_t
gettid(void)
{

	return syscall(SYS_gettid);
}

void foo()
{
	int a;
	printf("COUCOU de %ld dans process %ld my a is %p\n", gettid(), getpid(), &a);
	sleep(1);

}

/*
pthread_create()
	__OMP_XXX()
		foo()
			[RET]
			[REP]
			[a]

*/

int main(int argc, char ** argv)
{
#pragma omp parallel
	{
		while(1){
			foo();
		}
	}

	return 0;
}

