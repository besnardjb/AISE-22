#include <string.h>
#include <stdio.h>
size_t cnt = 0;
int mylib_puts(const char *s){
	cnt += strlen(s);
	return puts(s);
}

size_t mylib_nbchars()
{
	return cnt;
}

