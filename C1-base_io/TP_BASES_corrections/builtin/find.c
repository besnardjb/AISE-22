#include <stdio.h>
#include <dirent.h>
#include <regex.h>
#include <string.h>

int selection(const struct dirent * file)
{
	return 1;
}


int walk_dir(char *path, regex_t * search_pattern )
{
	struct dirent ** list = NULL;

	int nb_file = scandir(path, &list, selection, alphasort);

	if(nb_file < 0)
	{
		perror("scandir");
		return 1;
	}

	int i;

	for(i = 0 ; i < nb_file; i++ )
	{
		char * name = list[i]->d_name;

		if( regexec(search_pattern, name, 0, NULL, 0) == 0 )
			printf("%s\n", name);

		if(strcmp(name,".") && strcmp(name, ".."))
		{
			if( list[i]->d_type == DT_DIR )
			{
				char new_path[500];
				snprintf(new_path, 500, "%s/%s", path, name);
				int ret = walk_dir(new_path, search_pattern);
				if( ret != 0 )
					return ret;
			}
		}

	}


	return 0;
}



int main(int argc, char ** argv )
{
	if( argc != 3)
	{
		fprintf(stderr, "Syntaxe %s PATH PATTERN\n", argv[0]);
		return 1;
	}

	regex_t search_pattern;

	if( regcomp(&search_pattern, argv[2], REG_NOSUB) < 0 )
	{
		perror("regcomp");
		return 1;
	}

	return walk_dir(argv[1], &search_pattern);
}
