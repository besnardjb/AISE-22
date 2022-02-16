#ifndef _MYSTRING_H_
#define _MYSTRING_H_

typedef struct string_s
{
	char * data;
	size_t len;
} string;


string * str_create(const char * str );
void str_destroy( string * str);
void str_print( string * str);
void str_copy(string *s1, const string *s2);
int str_compare(const string *s1, const string* s2);
void str_append(string * str, string * app);
string * str_slice(string *str, size_t start, size_t end );
int str_regex(const string* s1, const string* pattern);

#endif /* ifndef -MYSTRING_H_ */
