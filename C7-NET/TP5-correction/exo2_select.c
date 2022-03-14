#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

ssize_t safe_write(int fd, void *buff,  size_t size)
{
	size_t written = 0;
	while( (size - written) != 0 )
	{
		errno = 0;
		ssize_t ret = write(fd, buff + written, size-written);

		if( ret < 0 )
		{
			if(errno == EINTR)
			{
				continue;
			}

			perror("write");
			return ret;
		}

		written += ret;
	}

	return 0;
}

int read_from_client ( int filedes )
{
	char buffer[512];
	int nbytes;
	nbytes = read ( filedes, buffer, 512 );

	if ( nbytes < 0 )
	{
		/* Read error. */
		perror ( "read" );
		exit ( EXIT_FAILURE );
	}
	else if ( nbytes == 0 )
	{
		return -1;
	}
	else
	{
		safe_write(filedes, buffer, nbytes);
		return 0;
	}
}


int main( int argc, char **argv )
{
	/* Valeur de retour de getaddrinfo
	 * avec les alternatives pour configurer
	 * le serveur en fonction des hints */
	struct addrinfo *res = NULL;
	/* Ces paramètres définissent comment
	 * le serveur doit être configuré */
	struct addrinfo hints;
	/* Toujours mettre la structure a 0 */
	memset( &hints, 0, sizeof( hints ) );
	/* Peu importe le protocole IPV4 (AF_INET)
	 * ou IPV6 (AF_INET6) */
	hints.ai_family = AF_UNSPEC;
	/* Nous voulons un socket TCP */
	hints.ai_socktype = SOCK_STREAM;
	/* Ce paramètre permet d'écouter
	 * hors de la machine locale */
	hints.ai_flags = AI_PASSIVE;

	/* Ce programme attend un paramètre qui est le port */
	if ( argc != 2 )
	{
		return 1;
	}

	/* Ici getaddrinfo permet de générer les
	 * configurations demandées */
	int ret = getaddrinfo( NULL, argv[1],
	                       &hints,
	                       &res );

	if ( ret < 0 )
	{
		herror( "getaddrinfo" );
		return 1;
	}

	struct addrinfo *tmp;

	int listen_sock = -1;

	int binded = 0;

	/* Nous allons parcourir les différentes
	 * configurations pour trouver une qui marche
	 * ces configurations sont définies par les hints */
	for ( tmp = res; tmp != NULL; tmp = tmp->ai_next )
	{
		/* On crée un socket */
		listen_sock = socket( tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol );

		if ( listen_sock < 0 )
		{
			perror( "sock" );
			continue;
		}

		/* On attache ce socket à un port donné (argument passé à getaddr) */
		ret = bind( listen_sock, tmp->ai_addr, tmp->ai_addrlen );

		if ( ret < 0 )
		{
			close( listen_sock );
			perror( "bind" );
			continue;
		}

		binded = 1;
		break;
	}

	if ( !binded )
	{
		fprintf( stderr, "Failed to bind on 0.0.0.0:%s\n", argv[1] );
		return 1;
	}

	/* On commence a ecouter */
	ret = listen( listen_sock, 2 );

	if ( ret < 0 )
	{
		perror( "listen" );
		return 1;
	}

	fd_set active_fd_set, read_fd_set;
	/* Initialize the set of active sockets. */
	FD_ZERO ( &active_fd_set );
	FD_SET ( listen_sock, &active_fd_set );

	while ( 1 )
	{
		/* Block until input arrives on one or more active sockets. */
		read_fd_set = active_fd_set;

		if ( select ( FD_SETSIZE, &read_fd_set, NULL, NULL, NULL ) < 0 )
		{
			perror ( "select" );
			exit ( EXIT_FAILURE );
		}

		int i;

		/* Service all the sockets with input pending. */
		for ( i = 0; i < FD_SETSIZE; ++i )
			if ( FD_ISSET ( i, &read_fd_set ) )
			{
				if ( i == listen_sock )
				{
					/* Event was on the listen Socket */
					struct sockaddr_in client_info;
					/* Connection request on original socket. */
					int new;
					unsigned int addr_size = sizeof ( struct sockaddr_in );
					new = accept ( listen_sock, ( struct sockaddr * ) &client_info,  &addr_size );

					if ( new < 0 )
					{
						perror ( "accept" );
						exit ( EXIT_FAILURE );
					}

					fprintf ( stderr,
					          "Server: connect from host %s, port %d.\n",
					          inet_ntoa ( client_info.sin_addr ),
					          ntohs ( client_info.sin_port ) );
					FD_SET ( new, &active_fd_set );
				}
				else
				{
					/* Data arriving on an already-connected socket. */
					if ( read_from_client ( i ) < 0 )
					{
						fprintf( stderr, "Client left\n" );
						close ( i );
						FD_CLR ( i, &active_fd_set );
					}
				}
			}
	}

	/* On ferme le serveur */
	close( listen_sock );
	return 0;
}
