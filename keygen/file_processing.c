/*
    Author: Rattle-Brain
    Description: This file contains functions to dump keys on files.
*/

#include <stdio.h>

// Create a file to store the public key
void dump_public_key(int n, int e) {
    FILE *file = fopen("key.pub.rbrsa", "w");
    fprintf(file, "%d %d", n, e);
    fclose(file);
}

// Create a file to store the private key
void dump_private_key(int n, int d) {
    FILE *file = fopen("key.rbrsa", "w");
    fprintf(file, "%d %d", n, d);
    fclose(file);
}