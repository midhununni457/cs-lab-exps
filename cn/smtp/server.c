#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd, newsock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(2525);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    listen(sockfd, 5);

    printf("SMTP Server running on port 2525\n");

    newsock = accept(sockfd, (struct sockaddr *)&client, &len);

    printf("Client connected\n\n");

    // Greeting
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "220 SMTP Server Ready\n");
    send(newsock, buffer, sizeof(buffer), 0);

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        read(newsock, buffer, sizeof(buffer));
        printf("Client: %s", buffer);

        // HELO
        if (strncmp(buffer, "HELO", 4) == 0) {
            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "250 Hello\n");
            send(newsock, buffer, sizeof(buffer), 0);
        }

        // MAIL FROM
        else if (strncmp(buffer, "MAIL FROM", 9) == 0) {
            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "250 OK\n");
            send(newsock, buffer, sizeof(buffer), 0);
        }

        // RCPT TO
        else if (strncmp(buffer, "RCPT TO", 7) == 0) {
            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "250 OK\n");
            send(newsock, buffer, sizeof(buffer), 0);
        }

        // DATA
        else if (strncmp(buffer, "DATA", 4) == 0) {
            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "354 End data with <CRLF>.<CRLF>\n");
            send(newsock, buffer, sizeof(buffer), 0);
            printf("\nEmail Message:\n");

            while (1) {
                memset(buffer, 0, sizeof(buffer));
                read(newsock, buffer, sizeof(buffer));

                if (strcmp(buffer, ".\n") == 0)
                    break;

                printf("%s", buffer);
            }
            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "250 Message Accepted\n");
            send(newsock, buffer, sizeof(buffer), 0);
        }

        // QUIT
        else if (strncmp(buffer, "QUIT", 4) == 0) {
            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "221 Bye\n");
            send(newsock, buffer, sizeof(buffer), 0);
            break;
        }
    }

    close(newsock);
    close(sockfd);

    return 0;
}