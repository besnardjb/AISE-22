#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    struct addrinfo * result = NULL;

    int ret = getaddrinfo(argv[1], argv[2], &hints, &result);


    if(ret < 0)
    {
        herror("getaddrinfo");
        return 1;
    }

    int sock = 0;
    int connected = 0;

    struct addrinfo *tmp;
    for(tmp = result; tmp != NULL; tmp=tmp->ai_next)
    {
        sock = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);

        if(sock < 0)
        {
            perror("socket");
            continue;
        }

        if( connect(sock, tmp->ai_addr, tmp->ai_addrlen) < 0)
        {
            perror("connect");
            continue;
        }

        connected = 1;
	break;
    }

    if(connected == 0)
    {
        fprintf(stderr, "PAS CONNECTED :-'(");
        return 1;
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
