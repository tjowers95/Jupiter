#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <sys/mman.h>

void print_keys(EC_KEY *key_object)
{
    const BIGNUM *bn_privkey = EC_KEY_get0_private_key(key_object);
    char *str_privkey = BN_bn2hex(bn_privkey);

    BN_CTX *ctx = BN_CTX_new();
    const EC_POINT *ecp_pubkey = EC_KEY_get0_public_key(key_object);
    const EC_GROUP *ec_group = EC_KEY_get0_group(key_object);
    char *str_pubkey = EC_POINT_point2hex(ec_group, ecp_pubkey, EC_GROUP_get_point_conversion_form(ec_group), ctx);

    printf("secp256k1\nPrivate Key:%s\nPublic Key: %s\n", str_privkey, str_pubkey);
    BN_CTX_free(ctx);

    return;
}
EC_KEY *generate_keys(int nid)
{
    EC_KEY *eckey_object;
    if (NULL == (eckey_object = EC_KEY_new_by_curve_name(nid)))
    {
        perror("EC_KEY_new_by_curve_name");
        exit(1);
    }
    if (1 != EC_KEY_generate_key(eckey_object))
    {
        perror("EC_KEY_generate_key");
        exit(1);
    }
    return eckey_object;
}