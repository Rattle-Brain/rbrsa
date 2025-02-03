#include "keygen/arithmetic_ops.h"
#include "keygen/file_utils.h"

#include <time.h>

int main() {

    RBRSA_PublicKey public_key;
    RBRSA_PrivateKey private_key;

    clock_t start_time = clock();

    generate_keys(&public_key, &private_key, VALID_PAIR_2048_a);

    clock_t end_time = clock();
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            dump_public_key(&public_key);
        }
        #pragma omp section
        {
            dump_private_key(&private_key);
        }
    }

    printf("Time taken to generate keys: %f seconds\n", time_spent);

    return 0;
}