#include "../ecop/EC.h"
#include <stdio.h>
#include <gmp.h>
#include <openssl/rand.h>

void alice_key_exchange(mpz_t a, mpz_t b, mpz_t p, ec_point *G);
void generate_secure_random(mpz_t result, mpz_t max_value);

int main(void) {
    mpz_t a, b, p;
    ec_point G;

    mpz_inits(a, b, p, G.x, G.y, NULL);

    printf("Enter a prime number p (decimal, >= 4 bits): ");
    mpz_inp_str(p, stdin, 10);
    printf("Enter coefficient a for the elliptic curve: ");
    mpz_inp_str(a, stdin, 10);
    printf("Enter coefficient b for the elliptic curve: ");
    mpz_inp_str(b, stdin, 10);

    printf("Enter the generator point G coordinates (x, y, z):\n");
    printf("x = ");
    mpz_inp_str(G.x, stdin, 10);
    printf("y = ");
    mpz_inp_str(G.y, stdin, 10);
    printf("z = ");
    scanf("%d", &G.z);

    alice_key_exchange(a, b, p, &G);

    mpz_clears(a, b, p, G.x, G.y, NULL);

    return 0;
}

void generate_secure_random(mpz_t result, mpz_t max_value) {
    int num_bytes = 4;
    unsigned char buffer[num_bytes];

    if (RAND_bytes(buffer, num_bytes) != 1) {
        fprintf(stderr, "Error generating secure random bytes\n");
        exit(1);
    }

    mpz_import(result, num_bytes, 1, sizeof(buffer[0]), 0, 0, buffer);

    mpz_mod(result, result, max_value);
}

void alice_key_exchange(mpz_t a, mpz_t b, mpz_t p, ec_point *G) {
    mpz_t k_A;
    ec_point A, B, shared_key;

    mpz_inits(k_A, A.x, A.y, B.x, B.y, shared_key.x, shared_key.y, NULL);

    generate_secure_random(k_A, p);
    gmp_printf("Random number: %Zd\n", k_A);

    A = point_multiplication(a, b, p, G, k_A);
    if (A.z == -1) {
        perror("G is not a point in the curve");
        mpz_clears(k_A, A.x, A.y, B.x, B.y, shared_key.x, shared_key.y, NULL);
        return;
    }
    gmp_printf("Alice's public key A = k_A * G is: A(%Zd, %Zd, %d)\n", A.x, A.y, A.z);

    printf("Enter the public key B from Bob (coordinates x, y, z):\n");
    printf("x = ");
    mpz_inp_str(B.x, stdin, 10);
    printf("y = ");
    mpz_inp_str(B.y, stdin, 10);
    printf("z = ");
    scanf("%d", &B.z);

    shared_key = point_multiplication(a, b, p, &B, k_A);
    if (B.z == -1) {
        perror("Something went wrong. B is not a point in the curve");
        mpz_clears(k_A, A.x, A.y, B.x, B.y, shared_key.x, shared_key.y, NULL);
        return;
    }
    gmp_printf("Alice's shared key K = k_A * B is: K(%Zd:%Zd:%d)\n", shared_key.x, shared_key.y, shared_key.z);

    mpz_clears(k_A, A.x, A.y, B.x, B.y, shared_key.x, shared_key.y, NULL);
}
