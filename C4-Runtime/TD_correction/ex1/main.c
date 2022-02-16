#include <stdio.h>
#include <mystring.h>
int main(int argc, char ** argv)
{
	string * a  = str_create("Hello, ");
	string * app = str_create("World !!\n");
	str_append(a, app);
	str_print( a );

	string * b = str_create( "Hello, World !!\n" );
	str_print( b );

	string * s = str_slice(a, 0, 2);
	str_print( s );

	if(str_compare(a, b) == 0)
		printf("a and b are identical\n");
	else
		printf("Error: a and b differs !\n");

	if(str_compare(a, s) > 0)
		printf("a is after s\n");
	else
		printf("Error: a is not marked as after s\n");

	str_copy(s, a);
	str_print(s);

	string* regex = str_create("^Hel[lL].*!.$");
	if(str_regex(a, regex))
		printf("Regex matches !\n");
	else
		printf("Error: Regex didn't match\n");

	str_destroy(a);
	str_destroy(b);
	str_destroy(s);
}

