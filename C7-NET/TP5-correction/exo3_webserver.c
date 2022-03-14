#include <sys/types.h>
#include <sys/stat.h>
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
#include <string.h>


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

ssize_t get_file_size(char * path)
{
	struct stat st;

	if( stat(path, &st) < 0)
	{
		return -1;
	}

	return st.st_size;
}



void sendfile(char * path, size_t size, int fd)
{
	char * data = malloc(size);

	FILE * f = fopen(path, "r");

	fread(data, 1, size, f);

	fclose(f);

	safe_write(fd, data, size);

	free(data);
}

void write_http_header(size_t len, int code, char * content_type, int fd)
{
	char header_buffer[512];

	char * response_type = NULL;

	switch (code)
	{
	case 200:
		response_type = "200 OK";
		break;
	case 404:
		response_type = "404 Not Found";
		break;
	}

	snprintf(header_buffer, 512, "HTTP/1.1 %s\nContent-Type: %s\nContent-Length: %ld\n\n", response_type, content_type, len);
	safe_write(fd, header_buffer, strlen(header_buffer));
	printf(header_buffer);
}

struct client_infos
{
	int client_socket;
};

void *client_loop( void *param )
{
	struct client_infos *info = ( struct client_infos * )param;

	char buffer[1024];

	FILE* socket = fdopen(info->client_socket, "rw+");

	if(!socket)
	{
		perror("fdopen");
		exit(1);
	}


	while(fgets(buffer, 1024, socket))
	{
		if(strlen(buffer) < 6)
		{
			continue;
		}

		char *http = strstr(buffer, " HTTP");

		if(http)
		{
			*http = '\0';
		}

		if( buffer[0] == 'G' && buffer[1] == 'E' && buffer[2] == 'T')
		{
			char * file_path = &buffer[4];

			printf("GET == '%s'\n", file_path);

			if(*file_path == '/' && strlen(file_path) == 1)
			{
				file_path="index.html";
			}
			else
			{
				/* Skip / */
				file_path++;
			}

			ssize_t content_size = get_file_size(file_path);

			if(0 < content_size )
			{
				write_http_header(content_size, 200, "text/html", info->client_socket);
				sendfile(file_path, content_size, info->client_socket);
				break;
			}
			else
			{
				write_http_header(0, 404, "text/html", info->client_socket);
			}
		}
	}


	fprintf( stderr, "Closing client socket\n" );
	/* On se déconnecte du client */
	fclose( socket );
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
