#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gmp.h>
#include <arpa/inet.h>


void RandomPrimes(mpz_t* p, mpz_t* q);
void Encryptor(char* plainText);

mpz_t n, e, d;

int main()
{
    mpz_init(n);
    mpz_init(e);
    mpz_init(d);
    char plainText[] = "This is an encrypted string";
    Encryptor(plainText);

    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(d);
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

long RabinMiller()
{
    return 0;
}

void GenerateKeys(void)
{   
    mpz_t p, q, phi, gcd; // Create p, q, n, phi, e, gdc and d as multi precision point integers
    mpz_init(p); // Initialise p, q n, phi, e, gdc and then d 
    mpz_init(q);
    mpz_init(phi);
    mpz_init(gcd);

    RandomPrimes(&p, &q); // Call the RandomPrimes function with the values for p and q

    mpz_mul(n, p, q); // Calculate n as the product of p and q
    mpz_sub_ui(p, p, 1); // Set p equal to p-1 
    mpz_sub_ui(q, q, 1); // Set q equal to q-1
    mpz_mul(phi, p, q); // Calculate the toitent function to p and q
    mpz_set_str(e, "65537", 10); // Set the exponent e equal to 65537
    mpz_gcdext(gcd, d, NULL, e, phi); // Calcualte the greatest common divisor for e and phi

    if (mpz_sgn(d) < 0)
    {
        mpz_add(d, d, phi);
    }

    //gmp_printf("GK n = %Zd\n", n);
    //gmp_printf("GK e = %Zd\n", e);
    //gmp_printf("GK d = %Zd\n", d);

    mpz_clear(p); // Clear the values
    mpz_clear(q);
    mpz_clear(phi);
    mpz_clear(gcd);
}


void Decryptor(mpz_t cipherText)
{
    mpz_t messageInt;
    
    //gmp_printf("n = %Zd\n", n);
    //gmp_printf("e = %Zd\n", e);
    gmp_printf("d = %Zd\n", d);
    mpz_init(messageInt);
    mpz_powm(messageInt, cipherText, d, n);
    gmp_printf("MessageInt = %Zd\n", messaegInt);

    // TODO Implement the string reversal process

    FILE *plainText_file = fopen("plaintext.txt", "w");
    mpz_out_str(plainText_file, 10, plainText);
    fclose(plainText_file);

    mpz_clear(plainText);
}


void Encryptor(char* plainText)
{
    size_t plainTextLength = strlen(plainText); // Create a size_t equal to the length of the plain text
    char bytes[plainTextLength+1]; // Declaring an array named bytes of size plainTextLength+1
    strncpy(bytes, plainText, plainTextLength); // Storing the characters from plainText inside bytes with a length of plainTextLength
    bytes[plainTextLength] = '\0'; // Adding a null terminator to the destination
    //printf("%s\n", bytes);

    int messageInteger = 0;
    for (int i = 0; i < plainTextLength; i++) { // Doing a bitshift left by 8 on the messageInterger and then ORing it with the 
        messageInteger = (messageInteger << 8) | bytes[i]; // current element of the bytes array
    }
    printf("Message interger: %d\n", messageInteger);

    mpz_t cipherText, messageInt;

    mpz_init(cipherText);
    mpz_init_set_si(messageInt, messageInteger); // This just makes the messageInteger an mpz_t

    GenerateKeys();
    gmp_printf("n = %Zd\n", n);
    gmp_printf("e = %Zd\n", e);
    //gmp_printf("messageInt = %Zd\n", messageInt);
    mpz_powm(cipherText, messageInt, e, n); // setting cipherText equal to the messageInt raised to e modulo n
    gmp_printf("The cipher text is: %Zd\n", cipherText);

    FILE *cipherText_file = fopen("ciphertext.txt", "w");
    mpz_out_str(cipherText_file, 10, cipherText);
    fclose(cipherText_file);

    Decryptor(cipherText);

    mpz_clear(cipherText);
    mpz_clear(messageInt);
}

