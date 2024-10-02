#include "EC.h"
#include <stdio.h>
#include <gmp.h>

int main(void) {
    mpz_t a, b, p, k_A;
    ec_point G, A;

    mpz_inits(a, b, p, k_A, NULL);

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

    printf("Enter the integer k_A: ");
    mpz_inp_str(k_A, stdin, 10);

    A = point_multiplication(a, b, p, G, k_A);

    gmp_printf("The result of A = k_A * G is A(%Zd, %Zd, %d)\n", A.x, A.y, A.z);

    mpz_clears(a, b, p, k_A, NULL);

    return 0;
}
