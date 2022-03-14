#include <sys/select.h>
#include <stdio.h>

int print_set(fd_set *set)
{
	int i;

	for(i = 0 ; i < FD_SETSIZE; i++)
	{
		if(FD_ISSET(i, set))
		{
			printf("%d is present\n", i);
		}

	}



}



int main(int argc, char ** argv)
{

	fd_set set;

	FD_ZERO(&set);

	FD_SET(19,&set);

	print_set(&set);

	return 0;
}
