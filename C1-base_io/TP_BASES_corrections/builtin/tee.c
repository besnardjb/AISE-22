#include <stdio.h>


int main(int argc, char ** argv){


	if(argc != 2)
	{
		return 1;
	}
	else {
		FILE * fdout = fopen(argv[1], "w");

		if(!fdout)
		{
			perror("fread");
			return 1;
		}

		char buff[500];
		int cnt;
		while( (cnt = fread(buff, sizeof(char),
						500, stdin)) != 0 )
		{

			if(cnt < 0)
			{
				perror("fread");
				return 1;
			}

			int ret = fwrite(buff, sizeof(char),
					cnt, stdout);

			if(ret < 0)
			{
				perror("fwrite");
				return 1;
			}

			ret = fwrite(buff, sizeof(char),
					cnt, fdout);

			if(ret < 0)
			{
				perror("fwrite");
				return 1;
			}

		}

		fclose(fdout);
	}

	return 0;
}



