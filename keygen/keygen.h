#include <gmp.h>
#include <omp.h>
#include <stdint.h>
#include <sys/types.h>

// Structure to store the public key
typedef struct {
    mpz_t n;            // Modulus
    mpz_t e;            // Public exponent
} RBRSA_PublicKey;

// Structure to store the private key
typedef struct {
    mpz_t n;            // Modulus
    mpz_t d;            // Private exponent
    mpz_t p;            // First prime factor
    mpz_t q;            // Second prime factor
    mpz_t dmodp;        // d mod (p-1)
    mpz_t dmodq;        // d mod (q-1)
    mpz_t qinv;         // q^(-1) mod p
} RBRSA_PrivateKey;

void generate_prime_factors(RBRSA_PrivateKey *private_key, int pair);
void generate_n(mpz_t n, const mpz_t p, const mpz_t q);
void generate_e(RBRSA_PublicKey *public_key, const mpz_t p, const mpz_t q);
void generate_d(RBRSA_PrivateKey *private_key, const mpz_t e);
void generate_dP(RBRSA_PrivateKey *private_key);
void generate_dQ(RBRSA_PrivateKey *private_key);
void generate_qInv(RBRSA_PrivateKey *private_key);
void generate_keys(RBRSA_PublicKey *public_key, RBRSA_PrivateKey *private_key, int pair);