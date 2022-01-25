#include <stdio.h>
#include <dirent.h>
#include <regex.h>

int main(int argc, char ** argv )
{
	char * path = argv[1];

	if( argc != 2)
	{
		path = ".";
	}

	struct dirent ** list = NULL;

	int nb_file = scandir(path, &list, NULL, alphasort);

	if(nb_file < 0)
	{
		perror("scandir");
		return 1;
	}

	int i;
	
	for(i = 0 ; i < nb_file; i++ )
	{
		printf("%s\n", list[i]->d_name);
	}

	return 0;
}
