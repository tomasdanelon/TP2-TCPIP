// client.c
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define PORT 8080
#define MAX_BUFFER 32000

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[MAX_BUFFER] = "Hello server"; //Substituir a mensagem aqui
    clock_t start, end;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Sending data and measuring time
    start = clock();
    send(sock, buffer, strlen(buffer), 0);
    read(sock, buffer, MAX_BUFFER);
    end = clock();

    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f\n", time_taken);

    return 0;
}
