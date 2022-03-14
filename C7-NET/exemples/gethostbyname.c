#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char **argv)
{
	if(argc < 2)
		return 1;

	struct hostent *ret = gethostbyname(argv[1]);

	if(!ret)
	{
		herror("gethostbyname");
		return 1;
	}


	printf("Host resolves to %s\n", ret->h_name);

	unsigned int i=0;
	while ( ret->h_addr_list[i] != NULL) {
		printf( "%s\n", inet_ntoa( *( struct in_addr*)( ret->h_addr_list[i])));
		i++;
	}


	return 0;
}
