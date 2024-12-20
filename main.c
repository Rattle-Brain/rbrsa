#include "keygen/arithmetic_ops.h"

int main() {

    int bits = 1024;
    uint8_t* prime = generate_prime_with_bit_length(bits);
    if (!prime) {
        printf("Invalid bit length\n");
        return 1;
    }

    unsigned long long max_value = (1 << bits) - 1;
    printf("Unsigned %d-bit range: 0 to %llu\n", bits, max_value);
    printf("Prime number with %d-bit length: %s\n", bits, prime);
    return 0;
}