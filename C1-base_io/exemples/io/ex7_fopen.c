#include <stdio.h>


int main(int argc, char ** argv)
{
	if(argc != 2)
	{
		printf("USAGE %s [PATH]\n", argv[0]);
		return 1;
	}

	FILE * fd = fopen(argv[1], "r");

	if(fd == NULL){
		perror("fopen");
		return 1;
	}



	fclose(fd);

	return 0;
}



