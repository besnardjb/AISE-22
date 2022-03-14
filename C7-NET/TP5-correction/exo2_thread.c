#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>  /* -lpthread */
#include <stdlib.h>
#include <signal.h>
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

struct client_infos
{
	int client_socket;
};


void *client_loop( void *param )
{
	struct client_infos *info = ( struct client_infos * )param;

	char buff[128];
	int ret = 0;

	while( 0 < (ret = read(info->client_socket, buff, 128) )  )
	{
		safe_write( info->client_socket, buff, ret );
	}

	fprintf( stderr, "Closing client socket\n" );
	/* On se déconnecte du client */
	close( info->client_socket );
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

	signal(SIGPIPE, SIG_IGN);

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

	/* On va maintenant accepter une connexion */
	/* Ceci sera remplis par
	 * accept et décrit le client (ip port)*/
	struct sockaddr client_info;
	socklen_t addr_len;
	fprintf( stderr, "Before accept\n" );

	while ( 1 )
	{
		/* On accepte un client et on récupére un nouveau FD */
		int client_socket = accept( listen_sock, &client_info, &addr_len );
		fprintf( stderr, "After accept\n" );

		if ( client_socket < 0 )
		{
			perror( "accept" );
			return 1;
		}

		struct client_infos *infos = ( struct client_infos * )malloc( sizeof( struct client_infos ) );

		infos->client_socket = client_socket;

		pthread_t th;

		pthread_create( &th, NULL, client_loop, ( void * ) infos );
	}

	/* On ferme le serveur */
	close( listen_sock );
	return 0;
}