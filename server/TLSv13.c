#include "TLSv13.h"
#include "BiT-FLaGS.h"
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int TCP_LiSTeN_oN(char *port)
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

void PRiNT_ReQueST(unsigned char *req, TLS_HaNDSHaKe* t)
{
    int i = 0;

    /* Record Header */
    printf("\t\t%s\n\t\t*************\n", "ReCoRD HeaDeR");

    for (i = 0; i < 5; i++)
    {
        if ((req[i] & 0xf0) != 0)
            printf("%hhx ", req[i]);
        else
            printf("0%hhx ", req[i]);
    }

    switch(t->record)
    {
        case 0x16:
            printf("\n0h16 -- HaNDSHaKe ReCoRD\n");
            break;
        case 0x00:
            printf("\n0h00 -- iNVaLiD ReCoRD\n");
            break;
        case 0x15:
            printf("\n0h15 -- aLeRT ReCoRD\n");
            break;
        case 0x17:
            printf("\n0h17 -- aPPLiCaTioN ReCoRD\n");
            break;
    }

    /*  Handshake Header  */
    if (t->record == 0x16)
    {
        printf("\n\t\t%s\n\t\t****************\n", "HaNDSHaKe HeaDeR");
        for (i = 5; i < 9; i++)
        {
            if ((req[i] & 0xf0) != 0)
                printf("%hhx ", req[i]);
            else
                printf("0%hhx ", req[i]);
        }

        switch (t->handshake)
        {
            case 0x01:
                printf("\n0h01 -- CLieNT HeLLo\n");
                break;
            case 0x02:
                printf("\n0h02 -- SeRVeR HeLLo\n");
                break;
            case 0x04:
                printf("\n0h04 -- NeW SeSSioN TiCKeT\n");
                break;
            case 0x05:
                printf("\n0h05 -- eND oF eaRLY DaTa\n");
                break;
            case 0x06:
                printf("\n0h06 -- HeLLo ReTRY ReQueST\n");
                break;
            case 0x08:
                printf("\n0h08 -- eNCRyPTeD eXTeNSioNS\n");
                break;
            case 0x0b:
                printf("\n0h0B -- CeRTiFiCaTe\n");
                break;
            case 0x0d:
                printf("\n0h0D -- CeRTiFiCaTe ReQueST");
                break;
            case 0x0f:
                printf("\n0h0F -- CeRTiFiCaTe VeRiFY\n");
                break;
            case 0x14:
                printf("\n0h14 -- FiNiSHeD\n");
                break;
            case 0x18:
                printf("\n0h18 -- KeY uPDaTe\n");
                break;
        }
    }

    /*   Client Version   */
    printf("\n\t\t%s\n\t\t**************\n", "CLieNT VeRSioN");
    for (i = 9; i < 11; i++)
    {
        if ((req[i] & 0xf0) != 0)
            printf("%hhx ", req[i]);
        else
            printf("0%hhx ", req[i]);
    }
    printf("\n\t\t%s\n\t\t*************\n", "CLieNT RaNDoM");
    for (i = 11; i < 43; i++)
    {
        if ((req[i] & 0xf0) != 0)
            printf("%hhx ", req[i]);
        else
            printf("0%hhx ", req[i]);
    }
    printf("\n\t\t%s\n\t\t**********\n", "SeSSioN iD");
    for (i = 43; i < 76; i++)
    {
        if ((req[i] & 0xf0) != 0)
            printf("%hhx ", req[i]);
        else
            printf("0%hhx ", req[i]);
    }


    /*  Cipher Suites  */
    printf("\n\t\t%s\n\t\t*************\n", "CiPHeR SuiTeS");
    int cipher_suites_length = (req[76] << 8) | ((req[77] ^ 0xffffff00) & 0x000000ff), cipher_suites_offset = 2 + cipher_suites_length, j = 0;
    uint16_t cipher_suites[5];
    for (i = 76, j = 0; i < (76 + cipher_suites_offset); i++)
    {
        if ((req[i] & 0xf0) != 0)
            printf("%hhx ", req[i]);
        else
            printf("0%hhx ", req[i]);

       if (i % 2 != 0 && i > 77 && j < 5)
            cipher_suites[j++] = (req[i - 1] << 8) | req[i];

    }

    for (int v = 0; v < j; v++)
    {
        if (v == 0)
            printf("\n");
        switch(cipher_suites[v])
        {
            case 0x1301:
                printf("0h1301 -- AES-128 GCM SHA-256\n");
                break;
            case 0x1302:
                printf("0h1302 -- AES-256 GCM SHA-384\n");
                break;
            case 0x1303:
                printf("0h1303 -- CHACHA-20 POLY-1305 SHA-256\n");
                break;
            case 0x1304:
                printf("0h1304 -- AES-128 CCM SHA-256\n");
                break;
            case 0x1305:
                printf("0h1305 -- AES-128 CCM-08 SHA-256\n");
                break;
        }
    }
    /*   Compression Methods   */
    printf("\n\t\t%s\n\t\t*******************\n", "CoMPReSSioN MeTHoDS");
    int compression_methods_length = req[76 + cipher_suites_offset], compression_methods_offset = 1 + compression_methods_length + cipher_suites_offset;
    for (i = (76 + cipher_suites_offset); i < (76 + compression_methods_offset); i++)
    {
        if ((req[i] & 0xf0) != 0)
            printf("%hhx ", req[i]);
        else
            printf("0%hhx ", req[i]);
    }

    printf("\n0h00 -- NuLL\n");

    /*   Extensions   */
    printf("\n\t\t%s\n\t\t**********\n", "EXTeNSioNS");
    int extension_length = (req[76 + compression_methods_offset] << 8) | ((req[76 + compression_methods_offset + 1] ^ 0xffffff00) & 0x000000ff), extension_offset = 2 + compression_methods_offset + extension_length, ec = 0, eco = 0;
    int register x = 0, y;
    uint8_t flag, *extension_contents[32];
    uint16_t extension_codes[32], extension_lengths[32];

    for (i = (76 + compression_methods_offset); i < (76 + extension_offset); i++)
    {
        if ((req[i] & 0xf0) != 0)
            printf("%hhx ", req[i]);
        else
            printf("0%hhx ", req[i]);

        if ((i - 76 - compression_methods_offset) < 2)
        {
            flag |= Bit8 | Bit7;
            continue;
        }

        if (!(flag & Bit8))
        {
            if (!(flag & Bit7))
                flag |= Bit7;
            else
                {
                    flag |= Bit8 | Bit3;
                    extension_lengths[x] = (req[i-1] << 8) | req[i];
                    extension_contents[x] = calloc(extension_lengths[x]);
                    y = extension_lengths[x++];
                }
        }
        else
            --y;

        if (y == 0) {
            flag &= ~(Bit4 | Bit3 | Bit2 | Bit1);
            eco = 0;
            continue;
        }

        if (flag & Bit3)
            if (!(flag & Bit4))
                flag |= Bit4
                        else
                extension_contents[eco++]

        if (!(flag & Bit1) && (flag & Bit8))
        {
            if (!(flag & Bit2))
                flag |= Bit2;
            else
                {
                    flag |= Bit1;
                    flag &= ~(Bit8 | Bit7);
                    extension_codes[ec++] = (req[i - 1] << 8) | req[i];
                }
        }

    }

    for (int i = 0; i < ec; i++)
    {
        printf("\n%hx\n", extension_codes[i]);
    }

    printf("%s", "\n");
}

TLS_HaNDSHaKe *iNCoMiNG(int so_fd)
{
    TLS_HaNDSHaKe *in = calloc(sizeof(*in), 1);

    if (0 > (in->fd = accept(so_fd, (struct sockaddr *){0}, &(socklen_t){sizeof(struct sockaddr)})))
    {
        perror("incoming");
        exit(1);
    }

    if ((in->len = recv(in->fd, in->data, 2048, 0)) < 0)
    {
        perror("recv");
        exit(1);
    }


    in->record = in->data[0];
    in->handshake = in->data[5];
    memcpy(in->random, in->data + 11, 32);

    uint32_t ciphers_length = (in->data[75] << 8) | ((in->data[76] ^ 0xffffff00) & 0x000000ff);
    in->ciphers = calloc(1, ciphers_length);
    memcpy(in->ciphers, in->data + 77, ciphers_length);

    uint32_t extensions_length = (in->data[77 + ciphers_length] << 8) | ((in->data[78 + ciphers_length] ^ 0xffffff00) & 0x000000ff);
    in->extensions = calloc(1, extensions_length);
    memcpy(in->extensions, in->data + 79 + ciphers_length, extensions_length);

    PRiNT_ReQueST(in->data, in);

    return in;
}

