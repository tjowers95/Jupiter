#include "TLSv13.h"
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int tcp_listen_on(char *port)
{
    int tcp_sock, enable = 1, rv;
    struct addrinfo criteria, *ptr, *interface;
    struct sockaddr_storage remote;

    memset(&criteria, 0, sizeof criteria);
    criteria.ai_family = AF_UNSPEC;
    criteria.ai_socktype = SOCK_STREAM;
    criteria.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, port, &criteria, &interface)) < 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return -1;
    }

    for (ptr = interface; ptr != NULL; ptr = ptr->ai_next)
    {
        if ((tcp_sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }
        if (setsockopt(tcp_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)
        {
            perror("setsockopt");
            continue;
        }
        if (bind(tcp_sock, ptr->ai_addr, ptr->ai_addrlen) == -1)
        {
            close(tcp_sock);
            perror("server: bind");
            continue;
        }
        break;
    }
    freeaddrinfo(interface);

    if (ptr == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }
    if (listen(tcp_sock, 10) == -1)
    {
        perror("listen");
        exit(1);
    }

    return tcp_sock;
}

void parse_request(char *req, int n)
{
    int i = 0;
    /* Record Header */
    printf("%s\n", "Record Header");
    for (i = 0; i < 5; i++)
    {
        printf("%hhx ", req[i]);
    }

    printf("\n%s\n", "Handshake Header");
    for (i = 5; i < 9; i++)
    {
        printf("%hhx ", req[i]);
    }
    printf("\n%s\n", "Client Version");
    for (i = 9; i < 11; i++)
    {
        printf("%hhx ", req[i]);
    }
    printf("\n%s\n", "Client Random");
    for (i = 11; i < 43; i++)
    {
        printf("%hhx ", req[i]);
    }
    printf("\n%s\n", "Session ID");
    for (i = 43; i < 76; i++)
    {
        printf("%hhx ", req[i]);
    }

    printf("\n%s\n", "Cipher Suites");
    int csbytes = (req[76] << 8) | ((req[77] ^ 0xffffff00) & 0x000000ff), csoff = 2 + csbytes;
    for (i = 76; i < (76 + csoff); i++)
    {
        printf("%hhx ", req[i]);
    }

    printf("\n%s\n", "Compression Methods");
    int cmbytes = req[76 + csoff], cmoff = 1 + cmbytes + csoff;
    for (i = (76 + csoff); i < (76 + cmoff); i++)
    {
        printf("%hhx ", req[i]);
    }

    printf("\n%s\n", "Extensions");
    int extbytes = (req[76 + cmoff] << 8) | ((req[76 + cmoff + 1] ^ 0xffffff00) & 0x000000ff), extoff = 2 + cmoff + extbytes;
    for (i = (76 + cmoff); i < (76 + extoff); i++)
    {
        printf("%hhx ", req[i]);
    }

    printf("%s", "\n");
}

struct raw_request_st incoming(int so_fd)
{
    struct raw_request_st in;
    if (0 > (in.so_fd = accept(so_fd, (struct sockaddr *){0}, sizeof(struct sockaddr))))
    {
        perror("incoming");
        exit(1);
    }
    in.bytes = recv(in.so_fd, in.data, 2048, 0);
}