#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	char path[400];
	getcwd(path, 400);
	printf("%s\n", path);
	
	return 0;
}
