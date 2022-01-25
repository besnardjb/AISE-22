#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>


int main(){

	time_t curtime;
	time(&curtime);

	printf("%ld %s",  curtime, ctime(&curtime));
	return 0;
}



