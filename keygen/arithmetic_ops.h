/*
    Header file for functions.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <gmp.h>

#define SUCCESS 0
#define FAILURE 1

// Acceptable bit lengths for prime p (AKA L)
#define MIN_L 1024
#define MID_L 2048
#define MAX_L 3072

// Acceptable bit lengths for prime q (AKA N)
#define MIN_N 160
#define MID_N 224
#define MAX_N 256

// Valid pair L/N strcut
typedef struct {
    int l;
    int n;
} valid_pair;

// Array of Valid pairs
static valid_pair valid_pairs[] = {
    {MIN_L, MIN_N},
    {MID_L, MID_N},
    {MID_L, MAX_N},
    {MAX_L, MAX_N}
};

#define VALID_PAIR_1024 0      // Acceptable pair of L/N (1024/160)
#define VALID_PAIR_2048_a 1    // Acceptable pair of L/N (2048/224)
#define VALID_PAIR_2048_b 2    // Acceptable pair of L/N (2048/256)
#define VALID_PAIR_3072 3      // Acceptable pair of L/N (3072/256)


// Function prototypes
int is_prime(unsigned long long n);
int generate_prime();
void generate_prime_with_bit_length(mpz_t prime, int bit_length);
void gcd(mpz_t result, const mpz_t a, const mpz_t b);
void lcm(mpz_t result, const mpz_t a, const mpz_t b);
int mod_inverse(mpz_t result, const mpz_t a, const mpz_t m);
void carmichael(mpz_t result, const mpz_t p, const mpz_t q);
void calculate_n(mpz_t n, const mpz_t p, const mpz_t q);
void calculate_e(mpz_t e, const mpz_t c_totient);
void calculate_d(mpz_t d, const mpz_t e, const mpz_t c_totient);