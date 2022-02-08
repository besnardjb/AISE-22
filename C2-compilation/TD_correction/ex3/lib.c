#define _GNU_SOURCE 1
#include <dlfcn.h>
#include <fcntl.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
size_t cnt = 0;

void* (*func)(size_t) = NULL;
void * malloc(size_t size)
{
	cnt +=1;

	if(func == NULL)
	{

		func = (void*(*)(size_t)) dlsym( RTLD_NEXT, "malloc");
		if(!func)
			abort();

	}
	return func(size);
}

__attribute__((destructor))
void end()
{
	printf("Count = %lu\n", cnt);
}

