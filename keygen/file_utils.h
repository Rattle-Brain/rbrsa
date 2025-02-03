#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keygen.h"

#define KEY_BUFF_SIZE 4096
#define LINE_SIZE 70

void serialize_rsa_public_key(FILE *file, RBRSA_PublicKey *pub_key);
void serialize_rsa_private_key(FILE *file, RBRSA_PrivateKey *priv_key);
void dump_public_key(RBRSA_PublicKey *pub_key);
void dump_private_key(RBRSA_PrivateKey *priv_key);
char* base64_encode(char* key_data);