#include "types.h"
#include "stat.h"
#include "user.h"

// Function to check if a character is alphanumeric
int isAlphaNumeric(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

// Function to convert uppercase characters to lowercase
char toLower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

// Function to check if a string is a palindrome
int isPalindrome(char *str, int len) {
    int start = 0;
    int end = len - 1;

    while (start < end) {
        // Skip non-alphanumeric characters from start
        while (start < len && !isAlphaNumeric(str[start]))
            start++;

        // Skip non-alphanumeric characters from end
        while (end >= 0 && !isAlphaNumeric(str[end]))
            end--;

        // If characters at start and end don't match, it's not a palindrome
        if (start < len && end >= 0 && toLower(str[start]) != toLower(str[end]))
            return 0;

        start++;
        end--;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(1, "Usage: palindrome [string]\n");
        exit();
    }

    // Check if the input string is a palindrome
    if (isPalindrome(argv[1], strlen(argv[1])))
        printf(1, "%s is a palindrome!\n", argv[1]);
    else
        printf(1, "%s is not a palindrome!\n", argv[1]);

    exit();
}