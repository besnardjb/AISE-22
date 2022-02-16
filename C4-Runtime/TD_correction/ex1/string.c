#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mystring.h>

string * str_create(const char * str )
{
	string * ret = malloc(sizeof(struct string_s));

	if(!str)
	{
		ret->data = NULL;
		ret->len  =0;
	}

	ret->len = strlen(str);
	ret->data = malloc(ret->len);
	memcpy(ret->data, str, ret->len );

	return ret;
}

void str_destroy( string * str)
{
	if(str->data)
		free(str->data);
	free(str);
}


void str_print( string * str)
{
	if(!str->data) return;
	char* out = malloc(str->len +1);
	memcpy(out, str->data, str->len);
	out[str->len] = '\0';
	printf("%s", out);
	free(out);
}

void str_copy(string *s1, const string *s2)
{
	size_t len = s2->len;

	if(len == 0)
	{
		if(s1->data)
			free(s1->data);
		s1->data = NULL;
		s1->len = 0;
		return;
	}
	free(s1->data);
	s1->data = malloc(len);
	s1->len = len;
	memcpy(s1, s2, len);
}


int str_compare(const string *s1, const string* s2)
{
	if(!s1->data || !s2->data) return -1;
	size_t len_1 = s1->len;
	size_t len_2 = s2->len;
	size_t i, j;
	for (i = 0, j= 0; i < len_1 && j < len_2; ++i, ++j) {
		if(s1->data[i] == s2->data[j])
			continue;
		
		if(s1->data[j] < s2->data[j])
			return -1;
		else
			return 1;
	}

	return (len_1 - len_2);
}


void str_append(string * str, string * app)
{
	int ldata = str->len;
	int lapp = app->len;

	if(app-> len == 0)
		return;

	char * appended = realloc(str->data, ldata + lapp + 1);
	memcpy(appended + ldata, app->data, lapp + 1);
	str->data = appended;
	str->len += lapp;
}

string * str_slice(string *str, size_t start, size_t end )
{
	if(!str->data) return str_create(NULL);
	int len = end - start + 1;
	char * slice = malloc( len );

	string * ret = malloc(sizeof(string));
	ret->data = slice;
	ret->len = len ;

	memcpy(ret->data, str->data + start, end-start );

	return ret;
}

#include <regex.h>
int str_regex(const string* s1, const string* pattern)
{
    int    status;
    regex_t    re;

    if (regcomp(&re, pattern->data, REG_EXTENDED|REG_NOSUB) != 0) {
            return(0);      /* Report error. */
        }
    status = regexec(&re, s1->data, (size_t) 0, NULL, 0);
    regfree(&re);
    if (status != 0) {
            return(0);      /* Report error. */
        }
    return(1);
}

