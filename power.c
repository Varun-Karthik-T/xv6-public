#include "types.h"
#include "user.h"

int power(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf(2, "Usage: %s <base> <exponent>\n", argv[0]);
        exit();
    }

    int base = atoi(argv[1]); // Convert string argument to integer
    int exponent = atoi(argv[2]); // Convert string argument to integer
    int result = power(base, exponent);
    
    printf(1, "%d raised to the power of %d is %d\n", base, exponent, result);

    exit();
}