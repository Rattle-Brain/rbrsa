/*
    Author: Rattle-Brain
    Description: This file contains functions to dump keys on files.
*/

#include "file_utils.h"
#include <stdio.h>

void serialize_rsa_public_key(FILE *file, RBRSA_PublicKey *pub_key) {
    char* buffer = malloc(KEY_BUFF_SIZE/4);
    char* encoded_buffer;
    char* line = malloc(LINE_SIZE * sizeof(char));
    int i = 0, c = 0;

    gmp_sprintf(buffer, "n: %Zd\ne: %Zd", pub_key->n, pub_key->e);
    
    encoded_buffer = base64_encode(buffer);
    int encode_buffer_length = strlen(encoded_buffer);

    while (i < encode_buffer_length) {
        line[c] = encoded_buffer[i];
        if (c == LINE_SIZE) {
            line[c+1] = '\0';
            fprintf(file, "%s\n", line);
            c = -1;
        }else if(i == encode_buffer_length - 1) {
            line[c+1] = '\0';
            fprintf(file, "%s", line);
        }
        c++;
        i++;
    }
    //fprintf(file, "%s", base64_encode(buffer));
    free(buffer);
    free(encoded_buffer);
    free(line);
    fprintf(file, "%s", base64_encode(buffer));
}

void serialize_rsa_private_key(FILE *file, RBRSA_PrivateKey *priv_key) {
    char* buffer = malloc(KEY_BUFF_SIZE * sizeof(char));
    char* encoded_buffer;
    char* line = malloc(LINE_SIZE * sizeof(char));
    int i = 0, c = 0;

    gmp_sprintf(buffer, "n: %Zd\nd: %Zd\np: %Zd\nq: %Zd\ndP: %Zd\ndQ: %Zd\nqInv: %Zd",
                priv_key->n, priv_key->d, priv_key->p, priv_key->q, priv_key->dmodp, priv_key->dmodq, priv_key->qinv);

    encoded_buffer = base64_encode(buffer);
    int encode_buffer_length = strlen(encoded_buffer);

    while (i < encode_buffer_length) {
        line[c] = encoded_buffer[i];
        if (c == LINE_SIZE) {
            line[c+1] = '\0';
            fprintf(file, "%s\n", line);
            c = -1;
        }else if(i == encode_buffer_length - 1) {
            line[c+1] = '\0';
            fprintf(file, "%s", line);
        }
        c++;
        i++;
    }
    //fprintf(file, "%s", base64_encode(buffer));
    free(buffer);
    free(encoded_buffer);
    free(line);
}

// Create a file to store the public key
void dump_public_key(RBRSA_PublicKey *pub_key) {
    FILE *file = fopen("key.rbrsa.pub", "w");
    fprintf(file, "-----BEGIN RBRSA PUBLIC KEY-----\n");
    serialize_rsa_public_key(file, pub_key);
    fprintf(file, "\n-----END RBRSA PUBLIC KEY-----\n");
    fclose(file);
}

// Create a file to store the private key
void dump_private_key(RBRSA_PrivateKey *priv_key) {
    FILE *file = fopen("key.rbrsa", "w");
    fprintf(file, "-----BEGIN RBRSA PRIVATE KEY-----\n");
    serialize_rsa_private_key(file, priv_key);
    fprintf(file, "\n-----END RBRSA PRIVATE KEY-----\n");
    fclose(file);
}

// Base64 encode the key data
char* base64_encode(char* key_data) {

    int rebalance = 0;

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
        encoded_key[encoded_length - 1 - i ] = '=';
    }

    return encoded_key;
}
