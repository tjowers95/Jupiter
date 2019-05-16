#ifndef _TLSv13_H
#define _TLSv13_H
#include <stdint.h>
typedef struct tls_handshake_st
{
    uint32_t fd, len;
    uint8_t record, handshake, random[32], *ciphers, *extensions;
    uint8_t supported_groups;
    uint8_t public_key[32], private_key[32];
    uint8_t data[2048];

} TLS_HaNDSHaKe;

int TCP_LiSTeN_oN(char *p);

TLS_HaNDSHaKe* iNCoMiNG(int s);

void PaRSe_HaNDSHaKe(TLS_HaNDSHaKe* t);

void SeT_GRouP(TLS_HaNDSHaKe* t);

void PRiNT_ReQueST(unsigned char *r, TLS_HaNDSHaKe* t);
#endif