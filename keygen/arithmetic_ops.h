/*
    Header file for functions.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <gmp.h>

#define SUCCESS 0
#define FAILURE -1

// Acceptable bit lengths for p (AKA L)
#define MIN_L 1024
#define MID_L 2048
#define MAX_L 3072

// Acceptable bit lengths for q (AKA N)
#define MIN_N 160
#define MID_N 22
#define MAX_N 3072

// Valid pair L/N strcut
typedef struct {
    int l;
    int n;
} valid_pair;

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