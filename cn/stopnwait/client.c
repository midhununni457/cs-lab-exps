#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

int main() {
    int sockfd;
    struct sockaddr_in server;

    char buffer[1024];
    char packet[1024];

    struct timeval tv;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_addr = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    printf("Connected to server\n");

    tv.tv_sec = 3;
    tv.tv_usec = 0;

    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv));

    while (i <= 5) {
        sprintf(packet, "Packet %d", i);
        printf("Sending &d\n", packet);

        send(sockfd, packet, strlen(packet), 0);

        memset(buffer, 0, sizeof(buffer));

        int n = read(sockfd, buffer, sizeof(buffer));

        if (n > 0 && strcmp(buffer, "ACK")) {
            printf("ACK received for packet %d\n", i);
            i++;
        } else {
            printf("Timeout.. resending packet %d...\n", i);
        }
    }
    printf("All packets sent successfully");
    close(sockfd);
    return 0;
}