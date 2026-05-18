#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server;

    char buffer[1024];

    int num1, num2;
    char op;

    printf("Enter expression(eg: x + y): ");
    scanf("%d %c %d", &num1, &op, &num2);

    sprintf(buffer, "%d %c %d", num1, op, num2);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    printf("Connected to server!\n");

    send(sockfd, buffer, sizeof(buffer), 0);

    memset(buffer, 0, sizeof(buffer));

    read(sockfd, buffer, sizeof(buffer));

    printf("Server response: %s\n", buffer);
    printf("Closing connection...\n");

    close(sockfd);

    return 0;
}