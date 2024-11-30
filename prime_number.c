#include <stdio.h>
#include <stdbool.h>
bool is_prime(int num);

int main() {
    int start, end;
    FILE *file;
    printf("Enter the range (start and end) to find prime numbers: ");
    scanf("%d %d", &start, &end);
    file = fopen("primes.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    fprintf(file, "Prime numbers between %d and %d:\n", start, end);
    for (int num = start; num <= end; num++) {
        if (is_prime(num)) {
            fprintf(file, "%d\n", num);
        }
    }

    printf("Prime numbers have been saved to 'primes.txt'.\n");
    fclose(file);

    return 0;
}
bool is_prime(int num) {
    if (num <= 1) {
        return false;
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}
