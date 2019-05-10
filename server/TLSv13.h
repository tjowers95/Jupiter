#ifndef _TLSv13_H
#define _TLSv13_H
struct raw_request_st
{
    uint so_fd, bytes;
    uint8_t data[];
};
struct tls_record_st
{
    uint meta;
    uint8_t header[5], data[0];
};

int tcp_listen_on(char *port);

struct raw_request_st incoming(int so_fd);
#endif