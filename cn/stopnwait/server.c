#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sockfd, newsock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    char buffer[1024];
    int ack_prob = 70;

    srand(time(0));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    listen(sockfd, 3);

    printf("Waiting for connection...\n");

    newsock = accept(sockfd, (struct sockaddr *)&client, &len);

    printf("Client connected.\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        
        int n = read(newsock, buffer, sizeof(buffer));

        if (n <= 0) break;

        printf("Received packet: %s\n", buffer);

        if (rand() % 100 < ack_prob) {
            send(newsock, "ACK", 4, 0);
            printf("ACK sent\n");
        } else {
            printf("ACK lost\n");
        }
    }

    close(newsock);
    close(sockfd);

    return 0;
}