#include <stdio.h>
#include <sys/ioctl.h>
#include <signal.h>


void term_size(void)
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	printf("Size is %d row %d cols\n", w.ws_row, w.ws_col);
}

void sig_handler(int sig)
{
	term_size();
}


int main(int argc, char ** argv)
{
	signal(SIGWINCH, sig_handler);

	while(1){}

	return 0;
}


