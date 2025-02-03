/*
    Contains the logic to generate the Private Key.
*/
#include "arithmetic_ops.h"
#include "keygen.h"

/**
    In a valid RSA private key with the second representation, the two factors p and q are the
    first two prime factors of the modulus n (i.e., r1 and r2), the exponents dP and dQ are
    positive integers less than p and q respectively satisfying
        e · dP ≡ 1 (mod (p–1))
        e · dQ ≡ 1 (mod (q–1))
    and the CRT coefficient qInv is a positive integer less than p satisfying
        q · qInv ≡ 1 (mod p).

    http://rfc.nop.hu/crypto/pkcs/pkcs-1v2-0a1.pdf [Page 3]
*/

// #########################################################
// #                                                       #
// #                   COMMON VALUES SECTION               #
// #                                                       #
// #########################################################

// Generate the prime factors p and q to calculate n (modulus)
void generate_prime_factors(RBRSA_PrivateKey *private_key, int pair) {
    mpz_init(private_key->p);
    mpz_init(private_key->q);

    generate_prime_with_bit_length(private_key->p, valid_pairs[pair].n);
    generate_prime_with_bit_length(private_key->q, valid_pairs[pair].l);
}

// Generate the modulus n = p * q
void generate_n(mpz_t n, const mpz_t p, const mpz_t q) {
    mpz_init(n);
    calculate_n(n, p, q);
}

// #########################################################
// #                                                       #
// #                   PUBLIC KEY SECTION                  #
// #                                                       #
// #########################################################

// Generate the public exponent e
void generate_e(RBRSA_PublicKey *public_key, const mpz_t p, const mpz_t q) {
    mpz_init(public_key->e);
    mpz_t c_totient;
    mpz_init(c_totient);

    carmichael(c_totient, p, q);
    calculate_e(public_key->e, c_totient);

    mpz_clear(c_totient);
}

// #########################################################
// #                                                       #
// #                   PRIVATE KEY SECTION                 #
// #                                                       #
// #########################################################

// Calculate the private exponent d as the modular inverse of e mod c_totient
void generate_d(RBRSA_PrivateKey *private_key, const mpz_t e) {
    mpz_init(private_key->d);
    mpz_t c_totient;
    mpz_init(c_totient);

    carmichael(c_totient, private_key->p, private_key->q);
    calculate_d(private_key->d, e, c_totient);

    mpz_clear(c_totient);
}

// Calculate the modular inverse dP such e · dP ≡ 1 (mod (p–1))
void generate_dP(RBRSA_PrivateKey *private_key) {
    mpz_init(private_key->dmodp);
    mpz_t p1;
    mpz_init(p1);
    mpz_sub_ui(p1, private_key->p, 1);
    mpz_mod(private_key->dmodp, private_key->d, p1);
    mpz_clear(p1);
}

// Calculate the modular inverse dQ such e · dQ ≡ 1 (mod (q–1))
void generate_dQ(RBRSA_PrivateKey *private_key) {
    mpz_init(private_key->dmodq);
    mpz_t q1;
    mpz_init(q1);
    mpz_sub_ui(q1, private_key->q, 1);
    mpz_mod(private_key->dmodq, private_key->d, q1);
    mpz_clear(q1);
}

// Calculate the CRT coefficient qInv such q · qInv ≡ 1 (mod p)
void generate_qInv(RBRSA_PrivateKey *private_key) {
    mpz_init(private_key->qinv);
    mod_inverse(private_key->qinv, private_key->q, private_key->p);
}

// #########################################################
// #                                                       #
// #                   KEY GENERATION SECTION              #
// #                                                       #
// #########################################################

// Generate the RSA public and private keys
void generate_keys(RBRSA_PublicKey *public_key, RBRSA_PrivateKey *private_key, int pair) {

    // Generate the prime factors p and q
    generate_prime_factors(private_key, pair);
    // Generate the modulus n = p * q and put it in pk and PubK
    generate_n(private_key->n, private_key->p, private_key->q);

    // Generate the public exponent e
    generate_e(public_key, private_key->p, private_key->q);

    // Generate the private exponent d
    generate_d(private_key, public_key->e);

    // Generate the modular inverse dP
    generate_dP(private_key);

    // Generate the modular inverse dQ
    generate_dQ(private_key);

    // Generate the CRT coefficient qInv
    generate_qInv(private_key);

    // Set the public key modulus to the private key modulus
    mpz_init_set(public_key->n, private_key->n);

}
