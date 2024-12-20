/*
    Header file for functions.c
*/

#include <stdlib.h>

int is_prime(int n);
int generate_prime();
int gcd(int a, int b);
int lcm(int a, int b);
int mod_inverse(int a, int m);
int carmichael(int p, int q);
int calculate_n(int p, int q);
int calculate_e(int p, int q);
int calculate_d(int e, int p, int q);