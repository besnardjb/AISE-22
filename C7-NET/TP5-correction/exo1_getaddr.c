#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main( int argc, char **argv )
{
	/* Liste des alternatives
	 * pour se connecter */
	struct addrinfo *res = NULL;
	/* Configuration souhaitée */
	struct addrinfo hints;
	/* Toujours mettre hints a 0 */
	memset( &hints, 0, sizeof( hints ) );
	/* On veut IPV4 ou IPV6, respectivement AF_INET ou AF_INET6 */
	hints.ai_family = AF_UNSPEC;
	/* On veut faire du TCP */
	hints.ai_socktype = SOCK_STREAM;
	/* On lance la résolution DNS
	 * argv[1] : nom de l'hôte
	 * argv[2] : port (exemple 80 pour http)
	 * */
	int ret = getaddrinfo( argv[1], argv[2],
	                       &hints,
	                       &res );

	if ( ret < 0 )
	{
		herror( "getaddrinfo" );
		return 1;
	}

	struct addrinfo *tmp;

	int sock = -1;

	int connected = 0;

	/* On parcours les alternative recues */
	for ( tmp = res; tmp != NULL; tmp = tmp->ai_next )
	{
		/* On crée un socket en suivant la configuration
		 * renvoyéee par getaddrinfo */
		sock = socket( tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol );

		if ( sock < 0 )
		{
			perror( "sock" );
			continue;
		}

		/* On tente de le connecter à l'adresse renvoyée par
		 * getaddrinfo et configurée par argv[1] et argv[2] */
		int ret = connect( sock, tmp->ai_addr, tmp->ai_addrlen );

		if ( ret < 0 )
		{
			close( sock );
			perror( "connect" );
			continue;
		}

		connected = 1;
		break;
	}

	if ( !connected )
	{
		fprintf( stderr, "Failed to connect to %s:%s\n", argv[1], argv[2] );
		return 1;
	}

	/* Si nous sommes là le socket est connecté
	 * avec succes on peut lire et ecrire dedans */
	/* Use the socket */
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

		/* On ecrit sur stdout ce que l'on a recu */
		write( STDOUT_FILENO, buff, ret );
	}

	/* On se déconnecte du serveur */
	close( sock );
	return 0;
}