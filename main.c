#include "keygen/arithmetic_ops.h"
#include "keygen/file_utils.h"

int main() {

    RBRSA_PublicKey public_key;
    RBRSA_PrivateKey private_key;

    generate_keys(&public_key, &private_key, VALID_PAIR_2048_a);

    dump_public_key(&public_key);
    dump_private_key(&private_key);

    return 0;
}