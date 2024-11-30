#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 1024

// Function prototypes
void encrypt_file(FILE *input, FILE *output, int shift);
void decrypt_file(FILE *input, FILE *output, int shift);
void process_file(char *filename, int shift, int mode);

int main() {
    char filename[100];
    int shift, choice;

    // Ask the user to input the file name and shift key
    printf("Enter the filename to encrypt/decrypt: ");
    scanf("%s", filename);
    printf("Enter the shift key (positive integer): ");
    scanf("%d", &shift);

    // Display options for encryption or decryption
    printf("Choose an operation:\n");
    printf("1. Encrypt File\n");
    printf("2. Decrypt File\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        process_file(filename, shift, 1);  // 1 for encryption
    } else if (choice == 2) {
        process_file(filename, shift, 0);  // 0 for decryption
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}

// Function to encrypt the file
void encrypt_file(FILE *input, FILE *output, int shift) {
    char ch;

    // Read each character from the input file and encrypt it
    while ((ch = fgetc(input)) != EOF) {
        fputc(ch + shift, output);  // Shift character to encrypt
    }

    printf("File encrypted successfully!\n");
}

// Function to decrypt the file
void decrypt_file(FILE *input, FILE *output, int shift) {
    char ch;

    // Read each character from the input file and decrypt it
    while ((ch = fgetc(input)) != EOF) {
        fputc(ch - shift, output);  // Reverse shift to decrypt
    }

    printf("File decrypted successfully!\n");
}

// Function to process the file (either encrypt or decrypt)
void process_file(char *filename, int shift, int mode) {
    FILE *input, *output;
    char output_filename[100];

    // Open the input file in read mode
    input = fopen(filename, "r");
    if (input == NULL) {
        printf("Error opening input file.\n");
        return;
    }

    // Create the output file name
    if (mode == 1) {
        sprintf(output_filename, "encrypted_%s", filename);
    } else {
        sprintf(output_filename, "decrypted_%s", filename);
    }

    // Open the output file in write mode
    output = fopen(output_filename, "w");
    if (output == NULL) {
        printf("Error opening output file.\n");
        fclose(input);
        return;
    }

    // Perform encryption or decryption based on the mode
    if (mode == 1) {
        encrypt_file(input, output, shift);
    } else {
        decrypt_file(input, output, shift);
    }

    // Close the files
    fclose(input);
    fclose(output);
}
