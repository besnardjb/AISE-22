#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv){
	if(argc != 3 )
		return 1;

	FILE * fd = fopen(argv[1], "a");

	if(!fd){
		perror("fopen");
		return 1;
	}

	size_t cnt;

	cnt = fwrite(argv[2], sizeof(char), strlen(argv[2]), fd);
	
	if( cnt == 0)
	{
		perror("fread");
		return 1;
	}

	fclose(fd);

	return 0;
}



