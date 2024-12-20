/*
    Author: Rattle-Brain

    Description: This file contains the functions to help the RBRSA keygen program.
*/
#include "arithmetic_ops.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <gmp.h>


// Array of Valid pairs
valid_pair valid_pairs[] = {
    {MIN_L, MIN_N},
    {MID_L, MID_N},
    {MID_L, MAX_N},
    {MAX_L, MAX_N}
};

// Function to check if a number is prime
int is_prime(unsigned long long n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;

    for (unsigned long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }

    return 1;
}


uint8_t* randomizer(int num_bytes){
    uint8_t* prime = malloc(num_bytes);
    int rand_byte;

    int i;
    for(i = 0; i < num_bytes; i++){
        srand(rand() + time(NULL));
        rand_byte = rand() % 256;
        prime[i] = rand_byte;

    }

    return prime;
}

// Function to generate a random prime number with a specified bit length
uint8_t* generate_prime_with_bit_length(int bit_length) {
    if(bit_length < 2) return NULL;
    int num_bytes = bit_length / 8;

    uint8_t* prime_array;
    mpz_t prime;
    mpz_init(prime);

    do {
        prime_array = randomizer(num_bytes);
        mpz_import(prime, bit_length, 1, 1, 0, 0, prime_array);
    } while (mpz_probab_prime_p(prime, 25) != 2);

    return prime_array;
}

// Function to calculate the greatest common divisor of two numbers
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Function to calculate the least commmon multiple of two numbers
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

// Function to calculate the modular multiplicative inverse
int mod_inverse(int a, int m) {
    a = a % m;

    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }

    return 1;
}

// Carmichael's totient function
int carmichael(int p, int q) {
    return lcm(p - 1, q - 1);
}


// Function to calculate n
int calculate_n(int p, int q) {
    return p * q;
}

// Function to calculate e such that 1 < e < c_totient and gcd(e, c_totient) = 1
// ensuring that e has a short bit length and small Hamming weight
int calculate_e(int p, int c_totient) {
    int e = 3;

    while (e < c_totient) {
        if (gcd(e, c_totient) == 1 && __builtin_popcount(e) <= 8) break;
        e += 2; // Increment by 2 to ensure e is odd
    }

    return e;
}

// Function to calculate d such that d * e ≡ 1 (mod c_totient)
int calculate_d(int e, int p, int q) {
    return mod_inverse(e, carmichael(p, q));
}

char* nomrbefunct(char p1, int p2, float p3, double* p4){

    return "This is a dummy function";
}

