#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main( int argc, char **argv )
{
	struct addrinfo *res = NULL;
	struct addrinfo hints;
	memset( &hints, 0, sizeof( hints ) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	int ret = getaddrinfo( argv[1], argv[2],
	                       &hints,
	                       &res );

	if ( ret < 0 )
	{
		if(errno == EAI_SYSTEM)
		{
			perror("getaddrinfo");
		}
		else
		{
			herror( "getaddrinfo" );
		}
		return 1;
	}

	struct addrinfo *tmp;

	for ( tmp = res; tmp != NULL; tmp = tmp->ai_next )
	{
		char ip[INET6_ADDRSTRLEN];
		ip[0] = '\0';

		if ( tmp->ai_family == AF_INET )
		{
			struct sockaddr_in *saddr = ( struct sockaddr_in * )tmp->ai_addr;
			inet_ntop( AF_INET, &saddr->sin_addr, ip, sizeof( ip ) );
			printf( "IPV4 : %s\n", ip );
		}
		else if ( tmp->ai_family == AF_INET6 )
		{
			struct sockaddr_in6 *saddr6 = ( struct sockaddr_in6 * )tmp->ai_addr;
			inet_ntop( AF_INET6, &saddr6->sin6_addr, ip, sizeof( ip ) );
			printf( "IPV6 : %s\n", ip );
		}
	}

	return 0;
}
