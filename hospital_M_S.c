#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 1024
void encrypt_file(FILE *input, FILE *output, int shift);
void decrypt_file(FILE *input, FILE *output, int shift);
void process_file(char *filename, int shift, int mode);

int main() {
    char filename[100];
    int shift, choice;
printf("Enter the filename to encrypt/decrypt: ");
    scanf("%s", filename);
    printf("Enter the shift key (positive integer): ");
    scanf("%d", &shift);
    printf("Choose an operation:\n");
    printf("1. Encrypt File\n");
    printf("2. Decrypt File\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        process_file(filename, shift, 1);  
    } else if (choice == 2) {
        process_file(filename, shift, 0); 
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
void encrypt_file(FILE *input, FILE *output, int shift) {
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        fputc(ch + shift, output); 
    }

    printf("File encrypted successfully!\n");
}
void decrypt_file(FILE *input, FILE *output, int shift) {
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        fputc(ch - shift, output); 
    }

    printf("File decrypted successfully!\n");
}
void process_file(char *filename, int shift, int mode) {
    FILE *input, *output;
    char output_filename[100];
    input = fopen(filename, "r");
    if (input == NULL) {
        printf("Error opening input file.\n");
        return;
    }
    if (mode == 1) {
        sprintf(output_filename, "encrypted_%s", filename);
    } else {
        sprintf(output_filename, "decrypted_%s", filename);
    }
    output = fopen(output_filename, "w");
    if (output == NULL) {
        printf("Error opening output file.\n");
        fclose(input);
        return;
    }
    if (mode == 1) {
        encrypt_file(input, output, shift);
    } else {
        decrypt_file(input, output, shift);
    }
    fclose(input);
    fclose(output);
}
