#include <stdlib.h>
#include <stdio.h>


int main() {
	int var, check = 0x04030201;
	char buf[40];

	fgets(buf,50,stdin);

	printf("check = %x\n", check);
	if (check == 0xdeadbeef) {
		printf("You Win !\n");
		abort();
	}
	return 0;
}

