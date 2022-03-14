#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	struct hostent * host = gethostbyname(argv[1]);

	if(!host)
	{
		herror("gethostbyname");
		return 1;
	}

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0)
	{
		perror("socket");
		return 0;
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(struct sockaddr_in));
	server.sin_family = host->h_addrtype;
	server.sin_port = htons(atoi(argv[2]));

	memcpy(&server.sin_addr, host->h_addr_list[0], host->h_length);

	int ret = connect(sock, (struct sockaddr*)&server, sizeof(struct sockaddr_in));

	if( ret < 0)
	{
		perror("connect");
		return 0;
	}

	char toto[128];

	snprintf(toto, 128, "COUCOU TOI\n");

	write(sock, toto, strlen(toto));

	while((ret = read(sock, toto, 128)) != 0)
	{
		write(0, toto, ret);
	}

	close(sock);

	return 0;
}
