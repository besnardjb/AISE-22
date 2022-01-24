#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

void alarmPrint(int signum){
	time_t curtime;
	time(&curtime);
	printf("current time is %s", ctime(&curtime));
	alarm(1);
}

int main(){
	signal(SIGALRM, alarmPrint);
	alarm(1);

	while(1) {
	}

	return 0;
}



