#ifndef _KEY_H
#define _KEY_H
#include <openssl/ec.h>
void PRiNT_KeYS(EC_KEY *key_object);
EC_KEY *GeNeRaTe_KeYS(int nid);
#endif