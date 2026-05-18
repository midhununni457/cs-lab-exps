#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(2525);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    // Receive Greeting
    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));
    printf("%s", buffer);

    // HELO
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "HELO localhost\n");
    send(sockfd, buffer, sizeof(buffer), 0);

    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));
    printf("%s", buffer);

    // MAIL FROM
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "MAIL FROM:<sender@gmail.com>\n");
    send(sockfd, buffer, sizeof(buffer), 0);

    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));
    printf("%s", buffer);

    // RCPT TO
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "RCPT TO:<receiver@gmail.com>\n");
    send(sockfd, buffer, sizeof(buffer), 0);

    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));
    printf("%s", buffer);

    // DATA
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "DATA\n");
    send(sockfd, buffer, sizeof(buffer), 0);

    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));
    printf("%s", buffer);

    // Message Body
    printf("\nEnter Email Message (End with '.' )\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        fgets(buffer, sizeof(buffer), stdin);
        send(sockfd, buffer, sizeof(buffer), 0);

        if (strcmp(buffer, ".\n") == 0)
            break;
    }

    // Receive Confirmation
    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));
    printf("%s", buffer);

    // QUIT
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "QUIT\n");
    send(sockfd, buffer, sizeof(buffer), 0);

    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));
    printf("%s", buffer);

    close(sockfd);

    return 0;
}