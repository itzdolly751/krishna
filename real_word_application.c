#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define PORT 8080

void* receive_message(int client_socket) {
    char buffer[BUFFER_SIZE];
    int read_size;

    while ((read_size = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[read_size] = '\0';
        printf("Received: %s\n", buffer);
    }

    return NULL;
}

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char message[BUFFER_SIZE];
    pthread_t receive_thread;

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IP address from text to binary form
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(1);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    printf("Connected to the server.\n");

    // Start receiving messages in a separate thread
    pthread_create(&receive_thread, NULL, receive_message, (void*)&client_socket);

    // Send messages to the server
    while (1) {
        printf("Enter message: ");
        fgets(message, sizeof(message), stdin);

        if (send(client_socket, message, strlen(message), 0) < 0) {
            perror("Send failed");
            exit(1);
        }
    }

    close(client_socket);
    return 0;
}
