#include <mylib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
	mylib_puts("Bonjours les gens !\n");
	mylib_puts("CA VA ?\n");

	printf("Nombre de caracteres : %lu\n", mylib_nbchars());

	return 0;
}
