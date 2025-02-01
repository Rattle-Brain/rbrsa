#include "keygen/arithmetic_ops.h"

int main() {

    int bits = MAX_L;
    mpz_t prime;
    generate_prime_with_bit_length(prime, bits);

    gmp_printf("Prime number with %d-bit length: %Zd\n", bits, prime);
    
    return 0;
}