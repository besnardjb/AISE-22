#include <stdio.h>


int main(int argc, char ** argv)
{
	int i;
	
#if 0
	for(i = 0 ; i < argc; i++)
	{
		printf("%d : %s\n", i, argv[i]);
	}
#endif

	while(*argv)
	{
		printf("%s\n", *argv);
		argv++;
	}


	return 0;
}
