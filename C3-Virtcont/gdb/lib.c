#include <stdio.h>

int gloubi = 0;

int foo(int a)
{
	gloubi++;
	if(a == 10)
	{
		char * p = NULL;
	//	*p = 1;
	}

	foo(a + 1);
}


