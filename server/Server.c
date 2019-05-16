#include "TLSv13.h"
#include "key.h"
#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    int tcp_sock = TCP_LiSTeN_oN("443");
    if (tcp_sock < 0)
    {
        perror("main: tcp_listen_on(443)");
        return -1;
    }

    TLS_HaNDSHaKe* request = iNCoMiNG(tcp_sock);

    EC_KEY *key = GeNeRaTe_KeYS(NID_secp256k1);

    return 0;
}
