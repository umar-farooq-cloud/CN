#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sock;
    struct sockaddr_in server;
    float result;

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Server address
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    // Receive result
    recv(sock, &result, sizeof(result), 0);

    printf("Value received from server: %.2f\n", result);

    close(sock);

    return 0;
}