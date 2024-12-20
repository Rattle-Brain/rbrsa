/*
    Author: Rattle-Brain

    Description: This file contains the functions to help the RBRSA keygen program.
*/
#include "functions.h"

// Function to check if a number is prime
int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }

    return 1;
}

// Function to generate a random prime number
int generate_prime() {
    int prime = rand() % 1000 + 1000;

    while (!is_prime(prime)) {
        prime++;
    }

    return prime;
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