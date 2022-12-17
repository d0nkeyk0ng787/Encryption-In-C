#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gmp.h>
#include <arpa/inet.h>


void RandomPrimes(mpz_t* p, mpz_t* q); // Define the 2 functions above main so it knows they exist.
void GenerateKeys(void);

mpz_t n, e, d;

int main()
{
    GenerateKeys(); // Call the GenerateKeys function
    return 0;
}

void RandomPrimes(mpz_t* p, mpz_t* q)
{
    int bitSize = 2048; // Create a bitSize to be used for our p and q
    unsigned long seed = time(0); // create a seed value for the random generate using time

    gmp_randstate_t state; // Create a random number generate state variable

    gmp_randinit_default(state); // Initiliase the random number generator state
    gmp_randseed_ui(state, seed); // Seed the rand num generator with our seed value

    mpz_urandomb(*p, state, bitSize); // Generate a random ints p and q based on our bitSize value
    mpz_urandomb(*q, state, bitSize);
    mpz_nextprime(*p, *p); // Set p equal to the next prime number after its current value
    mpz_nextprime(*q, *q); // Set q equal to the next prime number after its current value

    gmp_randclear(state); // Clear the value for state
}


void GenerateKeys(void)
{   
    mpz_t p, q, n, e, d, phi, gcd; // Create p, q, n, e, d, phi and gcd as multi precision point integers
    mpz_init(p); // Initialise p, q, n, e, d, phi, and then gcd 
    mpz_init(q);
    mpz_init(n);
    mpz_init(e);
    mpz_init(d);
    mpz_init(phi);
    mpz_init(gcd);

    RandomPrimes(&p, &q); // Call the RandomPrimes function with the values for p and q

    mpz_mul(n, p, q); // Calculate n as the product of p and q
    mpz_sub_ui(p, p, 1); // Set p equal to p-1 
    mpz_sub_ui(q, q, 1); // Set q equal to q-1
    mpz_mul(phi, p, q); // Calculate the toitent function to p and q
    mpz_set_str(e, "65537", 10); // Set the exponent e equal to 65537
    mpz_gcdext(gcd, d, NULL, e, phi); // Calcualte the greatest common divisor for e and phi

    if (mpz_sgn(d) < 0) // A simple check and add if the value of d is a negative
    {
        mpz_add(d, d, phi);
    }

    gmp_printf("n = %Zd\n", n);
    gmp_printf("e = %Zd\n", e);
    gmp_printf("d = %Zd\n", d);

    mpz_clear(p); // Clear the values
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(d);
    mpz_clear(phi);
    mpz_clear(gcd);
}

