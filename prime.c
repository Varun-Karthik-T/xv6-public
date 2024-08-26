#include "types.h"
#include "stat.h"
#include "user.h"

// Function to check if a number is prime
int isPrime(int n) {
    if (n <= 1) return 0;  // 0 and 1 are not prime numbers
    if (n <= 3) return 1;  // 2 and 3 are prime numbers

    // Check if n is divisible by 2 or 3
    if (n % 2 == 0 || n % 3 == 0) return 0;

    // Iterate from 5 to sqrt(n) checking divisibility by odd numbers
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;  // n is divisible by i or i+2
    }
    return 1;  // n is prime
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(1, "Usage: prime [number]\n");
        exit();
    }

    // Convert string argument to integer
    int n = atoi(argv[1]);

    // Check if the input number is prime
    if (isPrime(n))
        printf(1, "%d is a prime number!\n", n);
    else
        printf(1, "%d is not a prime number!\n", n);

    exit();
}