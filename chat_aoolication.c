#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_CLIENTS 10
#define PORT 8080
#define BUFFER_SIZE 1024

int client_sockets[MAX_CLIENTS];

void* handle_client(void* arg) {
    int client_socket = *((int*)arg);
    char buffer[BUFFER_SIZE];
    int read_size;

    while ((read_size = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[read_size] = '\0';
        printf("Client: %s\n", buffer);

        // Broadcast message to all connected clients
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (client_sockets[i] != 0) {
                send(client_sockets[i], buffer, strlen(buffer), 0);
            }
        }
    }

    // Client disconnected
    close(client_socket);
    return NULL;
}

int main() {
    int server_socket, client_socket, addr_len, i;
    struct sockaddr_in server_addr, client_addr;
    pthread_t thread_id;

    // Initialize client sockets to 0
    for (i = 0; i < MAX_CLIENTS; i++) {
        client_sockets[i] = 0;
    }

    // Create server socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 3) == -1) {
        perror("Listen failed");
        exit(1);
    }

    printf("Server is listening on port %d...\n", PORT);

    addr_len = sizeof(client_addr);
    while ((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, (socklen_t*)&addr_len)) >= 0) {
        printf("New client connected\n");

        // Add the new client socket to the list
        for (i = 0; i < MAX_CLIENTS; i++) {
            if (client_sockets[i] == 0) {
                client_sockets[i] = client_socket;
                break;
            }
        }

        // Create a new thread for each client
        if (pthread_create(&thread_id, NULL, handle_client, (void*)&client_socket) < 0) {
            perror("Thread creation failed");
            exit(1);
        }
    }

    if (client_socket < 0) {
        perror("Accept failed");
    }

    return 0;
}
