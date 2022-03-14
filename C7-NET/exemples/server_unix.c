#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main( int argc, char **argv )
{
	/* UNIX socket descriptor */
	struct sockaddr_un addr;
	/* Clear it */
	memset( &addr, 0, sizeof( addr ) );
	/* Set family to UNIX */
	addr.sun_family = AF_UNIX
	                  /* Set socket PATH */;
	strncpy( addr.sun_path, argv[1], sizeof( addr.sun_path ) - 1 );
	/* Create socket FD */
	int listen_socket = socket( AF_UNIX, SOCK_STREAM, 0 );

	if ( listen_socket < 0 )
	{
		perror( "socket" );
		return 1;
	}

	/* BIND the socket to UNIX socket */
	int ret = bind( listen_socket, ( struct sockaddr * )&addr, sizeof( addr ) );

	if ( ret < 0 )
	{
		perror( "bind" );
		fprintf( stderr, "Failed to bind on 0.0.0.0:%s\n", argv[1] );
		return 1;
	}

	/* On commence a ecouter */
	ret = listen( listen_socket, 2 );

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
	int cnt = 0;

	while ( cnt < 5 )
	{
		fprintf( stderr, "Before accept\n" );
		/* On accepte un client et on récupére un nouveau FD */
		int client_socket = accept( listen_socket, &client_info, &addr_len );
		fprintf( stderr, "After accept\n" );

		if ( client_socket < 0 )
		{
			perror( "accept" );
			return 1;
		}

		/* On envoie salut a celui qui s'est connecté */
		write( client_socket, "SALUT!\n", strlen( "SALUT!\n" ) );
		fprintf( stderr, "Closing client socket\n" );
		/* On se déconnecte du client */
		close( client_socket );
		cnt++;
	}

	/* On ferme le serveur */
	close( listen_socket );

	unlink(argv[1]);

	return 0;
}