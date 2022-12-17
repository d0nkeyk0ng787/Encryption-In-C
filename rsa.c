#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>


void RandomPrimes(mpz_t* p, mpz_t* q);

int main(void)
{
    mpz_t p, q;
    mpz_init(p);
    mpz_init(q);

    RandomPrimes(&p, &q);

    gmp_printf("p = %Zd\n", p);
    gmp_printf("q = %Zd\n", q);

    mpz_clear(p);
    mpz_clear(q);

    char * plainText;

    printf("Enter a string to be encrypted: ");
    scanf("%s", &plainText);
    //printf("%d", RandomPrimes(100000000)); 

    // printf(Encryptor());
    // printf(Decryptor());
    return 0;
}

void RandomPrimes(mpz_t* p, mpz_t* q)
{
    int bitSize = 2048;
    gmp_randstate_t state;

    gmp_randinit_default(state);

    mpz_urandomb(p, state, bitSize);
    mpz_urandomb(q, state, bitSize);
    mpz_nextprime(p, p);
    mpz_nextprime(q, q);

    gmp_randclear(state);
}

long RabinMiller()
{
    return 0;
}

void GenerateKeys()
{
    printf("Place holder");
}

char * Encryptor()
{
    return "test";
}

char * Decryptor()
{
    return "\ntest2";
}

