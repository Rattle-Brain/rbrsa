/*
    Author: Rattle-Brain
    Description: This file contains functions to dump keys on files.
*/

#include "file_utils.h"
#include <stdio.h>

void serialize_rsa_public_key(FILE *file, RBRSA_PublicKey *pub_key) {
    char* buffer = malloc(4096);
    gmp_fprintf(file, "-----BEGIN RBRSA PUBLIC KEY-----\n");
    fprintf(file, "RBRSA%lu", (sizeof(pub_key->n) * 8));
    gmp_sprintf(buffer, "n: %Zd\ne: %Zd", pub_key->n, pub_key->e);
    base64_encode(buffer);
    fputs(base64_encode(buffer), file);
    gmp_fprintf(file, "\n-----END RBRSA PUBLIC KEY-----\n");
}

void serialize_rsa_private_key(FILE *file, RBRSA_PrivateKey *priv_key) {
    char* buffer = malloc(4096);
    gmp_fprintf(file, "-----BEGIN RBRSA PRIVATE KEY-----\n");
    fprintf(file, "RBRSA%lu", (sizeof(priv_key->n) * 8));
    gmp_sprintf(buffer, "n: %Zd\nd: %Zd\np: %Zd\nq: %Zd\ndP: %Zd\ndQ: %Zd\nqInv: %Zd",
                priv_key->n, priv_key->d, priv_key->p, priv_key->q, priv_key->dmodp, priv_key->dmodq, priv_key->qinv);
    base64_encode(buffer);
    fputs(base64_encode(buffer), file);
    gmp_fprintf(file, "\n-----END RBRSA PRIVATE KEY-----\n");
    free(buffer);
}

// Create a file to store the public key
void dump_public_key(RBRSA_PublicKey *pub_key) {
    FILE *file = fopen("key.pub.rbrsa", "w");
    serialize_rsa_public_key(file, pub_key);
    fclose(file);
}

// Create a file to store the private key
void dump_private_key(RBRSA_PrivateKey *priv_key) {
    FILE *file = fopen("key.rbrsa", "w");
    serialize_rsa_private_key(file, priv_key);
    fclose(file);
}

// Base64 encode the key data
char* base64_encode(char* key_data) {
    // Base64 encoding
    size_t key_data_length = strlen(key_data);
    size_t encoded_length = 4 * ((key_data_length + 2) / 3);
    char *encoded_key = (char*)calloc(encoded_length + 1, sizeof(char));
    // Base64 encoding table
    static char *base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // Encode the key data
    for (size_t i = 0, j = 0; i < key_data_length;) {
        uint32_t octet_a = i < key_data_length ? (unsigned char)key_data[i++] : 0;
        uint32_t octet_b = i < key_data_length ? (unsigned char)key_data[i++] : 0;
        uint32_t octet_c = i < key_data_length ? (unsigned char)key_data[i++] : 0;
        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_key[j++] = base64_table[(triple >> 3 * 6) & 0x3F];
        encoded_key[j++] = base64_table[(triple >> 2 * 6) & 0x3F];
        encoded_key[j++] = base64_table[(triple >> 1 * 6) & 0x3F];
        encoded_key[j++] = base64_table[(triple >> 0 * 6) & 0x3F];
    }

    // Pad the encoded key
    for (size_t i = 0; i < (3 - key_data_length % 3) % 3; i++) {
        encoded_key[encoded_length - 1 - i] = '=';
    }

    return encoded_key;
}
