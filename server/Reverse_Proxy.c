#include "http2.h"
#include "key.h"
#include <openssl/evp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    int tcp_sock = tcp_listen_on("443");
    if (tcp_sock < 0)
    {
        perror("main: tcp_listen_on(443)");
        return -1;
    }

    char res[2048];
    EC_KEY *key = generate_keys(NID_secp256k1);
    res[0] = 0x16;
    res[1] = 0x03;
    res[2] = 0x03;
    res[2] = 0x00; //res[3] bytes of handshake message remaining
    res[4] = 0x02;
    //res[5] = 0x00; res[6] = 0x00; res[7] = 0x76; bytes of server hello remaining
    res[8] = 0x03;
    res[9] = 0x03;
    for (int r = 0; r < 32; r++)
    {
        res[r + 10] = (char)(rand() % 0xFF);
    }
    return 0;
}
