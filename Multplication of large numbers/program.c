#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to reverse a string
void reverse(char *str) {
    int length = strlen(str);
    int i, j;
    char temp;
    
    for (i = 0, j = length - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

// Function to multiply two large numbers represented as strings
char* multiplyStrings(char *num1, char *num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    
    // Result can have at most len1 + len2 digits
    int resultLen = len1 + len2;
    char *result = (char *)malloc(resultLen + 1); // +1 for the null terminator
    if (result == NULL) {
        printf("Memory allocation error.\n");
        exit(1);
    }
    
    // Initialize result to '0'
    for (int i = 0; i <= resultLen; i++) {
        result[i] = '0';
    }
    result[resultLen] = '\0';

    // Multiply each digit of num1 with num2 and accumulate the result
    for (int i = 0; i < len1; i++) {
        int carry = 0;
        int digit1 = num1[i] - '0';

        for (int j = 0; j < len2; j++) {
            int digit2 = num2[j] - '0';
            int product = (result[i + j] - '0') + digit1 * digit2 + carry;
            
            carry = product / 10;
            result[i + j] = (product % 10) + '0';
        }

        // Handle carry after each row multiplication
        if (carry > 0) {
            result[i + len2] += carry;
        }
    }

    // Remove leading zeros by reversing the result
    reverse(result);
    while (result[0] == '0' && result[1] != '\0') {
        memmove(result, result + 1, resultLen);
    }

    return result;
}

int main() {
    char num1[] = "123456789";
    char num2[] = "987654321";

    char *result = multiplyStrings(num1, num2);

    printf("Product: %s\n", result);

    free(result); // Don't forget to free the allocated memory
    return 0;
}
