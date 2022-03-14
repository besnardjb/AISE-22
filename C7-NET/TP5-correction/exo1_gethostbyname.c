#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main( int argc, char **argv )
{
	/* Argument check */
	if ( argc != 3 )
	{
		return 1;
	}

	/* Name resolution */
	struct hostent *server_info = gethostbyname( argv[1] );

	if ( !server_info )
	{
		herror( "gethostbyname" );
		return 1;
	}

	/* Create Socket */
	int sock = socket( AF_INET, SOCK_STREAM, 0 );

	if ( sock < 0 )
	{
		perror( "socket" );
		return 1;
	}

	/* Configure client socket */
	struct sockaddr_in server_conf;
	/* Insert address family */
	server_conf.sin_family = server_info->h_addrtype;
	/* Insert PORT */
	server_conf.sin_port = htons( atoi( argv[2] ) );
	/* Copy destination addr from server_info */
	memcpy( &server_conf.sin_addr, server_info->h_addr_list[0], server_info->h_length );

	/* Connect the socket to the server */
	if ( connect( sock, ( struct sockaddr * )&server_conf, sizeof( struct sockaddr_in ) ) < 0 )
	{
		perror( "Connect" );
		return 1;
	}

	/* Start READING from the server */
	char buff[500];

	/* Read from sock */
	while ( 1 )
	{
		ssize_t ret = read( sock, buff, 500 );

		if ( ret == -1 )
		{
			if ( errno == EINTR )
			{
				continue;
			}
			else
			{
				perror( "read" );
				break;
			}
		}

		if ( ret == 0 )
		{
			break;
		}

		write( STDOUT_FILENO, buff, ret );
	}

	close( sock );
}