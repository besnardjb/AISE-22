#define _DEFAULT_SOURCE
#include <stdio.h>
#include <dirent.h>
#include <regex.h>

char * file_type(unsigned char t)
{
	switch(t)
	{
		case DT_BLK:
		return "Block Device";
		case DT_CHR:
		return "Char Device";
		case DT_DIR:
		return "Directory";
		case DT_FIFO:
		return "Named PIPE";
		case DT_LNK:
		return "Symbolic link";
		case DT_REG:
		return "Regular file";
		case DT_SOCK:
		return "UNIX socket";
	}

	return "Uknown";
}



int main(int argc, char ** argv )
{
	if( argc != 1)
	{
		fprintf(stderr, "Syntaxe %s takes no argument (only list current dir)\n", argv[0]);
		return 1;
	}
	
	/* This code only support current dir */
	DIR* dir = opendir(".");
	
	if( dir == NULL )
	{
		perror("opendir");
		return 1;
	}

	struct dirent * entry = NULL;
	while( (entry = readdir(dir)) != NULL)
	{
		printf("%s of type %s\n", entry->d_name, file_type(entry->d_type));
	}

	return 0;
}
