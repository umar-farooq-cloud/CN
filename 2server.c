#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>

int main()
{
    int server_fd, client1, client2;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    float value, result;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    // Bind
    bind(server_fd, (struct sockaddr *)&server, sizeof(server));

    // Listen
    listen(server_fd, 2);

    printf("Server waiting for Client 1...\n");

    // Accept Client 1
    client1 = accept(server_fd, (struct sockaddr *)&client, &len);

    // Receive float
    recv(client1, &value, sizeof(value), 0);

    // Calculate power 1.5
    result = pow(value, 1.5);

    printf("Value received: %.2f\n", value);
    printf("Value to send: %.2f\n", result);

    close(client1);

    printf("Waiting for Client 2...\n");

    // Accept Client 2
    client2 = accept(server_fd, (struct sockaddr *)&client, &len);

    // Send result
    send(client2, &result, sizeof(result), 0);

    close(client2);
    close(server_fd);

    return 0;
}