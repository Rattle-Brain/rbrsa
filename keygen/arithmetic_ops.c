/*
    Author: Rattle-Brain

    Description: This file contains the functions to help the RBRSA keygen program.
*/
#include "arithmetic_ops.h"
#include <gmp.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>


// Function to generate a random prime number with a specified bit length
void generate_prime_with_bit_length(mpz_t prime, int bit_length) {
    if (bit_length < 2) {
        fprintf(stderr, "Error: Bit length must be at least 2.\n");
        exit(EXIT_FAILURE);
    }

    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, time(NULL));

    do {
        mpz_urandomb(prime, state, bit_length);
        mpz_setbit(prime, bit_length - 1);          // Ensure the number is of the desired bit length
        mpz_setbit(prime, 0);                       // Ensure it's odd
    } while (mpz_probab_prime_p(prime, 50) == 0);   // Use Miller-Rabin test

    gmp_randclear(state);
}


// Function to calculate the greatest common divisor of two numbers
void gcd(mpz_t result, const mpz_t a, const mpz_t b) {
    mpz_gcd(result, a, b);
}

// Function to calculate the least common multiple of two numbers
void lcm(mpz_t result, const mpz_t a, const mpz_t b) {
    mpz_lcm(result, a, b);
}

// Function to calculate the modular multiplicative inverse
int mod_inverse(mpz_t result, const mpz_t a, const mpz_t m) {
    if (mpz_invert(result, a, m) == 0) {
        perror("Error: Modular inverse does not exist.\n");
        return FAILURE;
    }
    return SUCCESS;
}

// Function to calculate Carmichael's totient function (λ(n) = lcm(p-1, q-1))
void carmichael(mpz_t result, const mpz_t p, const mpz_t q) {
    mpz_t p1, q1;
    mpz_inits(p1, q1, NULL);

    mpz_sub_ui(p1, p, 1);
    mpz_sub_ui(q1, q, 1);
    lcm(result, p1, q1);

    mpz_clears(p1, q1, NULL);
}

// Function to calculate n = p * q
void calculate_n(mpz_t n, const mpz_t p, const mpz_t q) {
    mpz_mul(n, p, q);
}

// Function to calculate e such that 1 < e < c_totient and gcd(e, c_totient) = 1
void calculate_e(mpz_t e, const mpz_t c_totient) {
    mpz_set_ui(e, 65537);               // Use common RSA public exponent
    mpz_t gcd_result;
    mpz_init(gcd_result);

    gcd(gcd_result, e, c_totient);
    if (mpz_cmp_ui(gcd_result, 1) != SUCCESS) {
        fprintf(stderr, "Error: e is not coprime with Carmichael's totient.\n");
        exit(FAILURE);
    }

    mpz_clear(gcd_result);
}

// Function to calculate d such that d * e ≡ 1 (mod c_totient)
void calculate_d(mpz_t d, const mpz_t e, const mpz_t c_totient) {
    if (mod_inverse(d, e, c_totient) != SUCCESS) {
        fprintf(stderr, "Error: Failed to compute modular inverse for d.\n");
        exit(FAILURE);
    }
}

