#ifndef _KEY_H
#define _KEY_H
#include <openssl/ec.h>
void print_keys(EC_KEY *key_object);
EC_KEY *generate_keys(int nid);
#endif