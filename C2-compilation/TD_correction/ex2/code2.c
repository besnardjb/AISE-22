#include <string.h>
#include <stdio.h>
#include <stdlib.h>
size_t cnt = 0;
int mylib_puts(const char *s){
	cnt += strlen(s);

	char *s_dup = strdup(s);
	size_t size = strlen(s);
	int i;
	for (i = 0; i < size; ++i) {
		s_dup[size-1-i] = s[i];
	}
	int ret = puts(s_dup);
	free(s_dup);
	return ret;
}

size_t mylib_nbchars()
{
	return cnt;
}

