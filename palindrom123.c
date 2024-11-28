 
#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int i, j, isPalindrome = 1;

    printf("Enter a string: ");
    scanf("%s", str);

    j = strlen(str) - 1;

    for (i = 0; i < strlen(str) / 2; i++) {
        if (str[i] != str[j]) {
            isPalindrome = 0;
            break;
        }
        j--;
    }

    if (isPalindrome) {
        printf("%s is a palindrome\n", str);
    } else {
        printf("%s is not a palindrome\n", str);
    }

    return 0;
}