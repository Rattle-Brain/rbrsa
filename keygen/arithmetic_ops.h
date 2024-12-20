/*
    Header file for functions.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>

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
uint8_t* generate_prime_with_bit_length(int bit_length);
int gcd(int a, int b);
int lcm(int a, int b);
int mod_inverse(int a, int m);
int carmichael(int p, int q);
int calculate_n(int p, int q);
int calculate_e(int p, int q);
int calculate_d(int e, int p, int q);