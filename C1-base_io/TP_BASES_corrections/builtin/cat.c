#include <stdio.h>


int main(int argc, char ** argv){


	if(argc == 1)
	{
		int c;
		while((c = getchar()) != (int) EOF )
			putchar(c);
	}
	else {
		FILE * fd = fopen(argv[1], "r");

		if(!fd){
			perror("fopen");
			return 1;
		}

		char buff[500];
		int cnt;
		while( (cnt = fread(buff, sizeof(char),
						500, fd)) != 0 )
		{

			if(cnt < 0)
			{
				perror("fread");
				return 1;
			}

			//fprintf(stderr, "cnt %d\n", cnt);

			int ret = fwrite(buff, sizeof(char),
					cnt, stdout);

			if(ret < 0)
			{
				perror("fwrite");
				return 1;
			}

		}
		fclose(fd);
	}

	return 0;
}



