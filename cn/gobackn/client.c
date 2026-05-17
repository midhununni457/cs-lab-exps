#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define WINDOW_SIZE 3
#define TOTAL_PACKETS 5

int main() {

    int sockfd;

    struct sockaddr_in server;

    char buffer[1024];
    char packet[100];

    struct timeval tv;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    printf("Connected to server\n\n");

    // Timeout = 3 seconds
    tv.tv_sec = 3;
    tv.tv_usec = 0;

    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,
               (const char *)&tv, sizeof(tv));

    int base = 1;
    int next = 1;

    while (base <= TOTAL_PACKETS) {

        // Send packets inside window
        while (next < base + WINDOW_SIZE &&
               next <= TOTAL_PACKETS) {

            sprintf(packet, "%d", next);

            printf("Sending Packet %d\n", next);

            send(sockfd, packet, strlen(packet), 0);

            next++;
        }

        memset(buffer, 0, sizeof(buffer));

        int n = read(sockfd, buffer, sizeof(buffer));

        if (n > 0) {

            int ack = atoi(buffer);

            printf("ACK received for Packet %d\n\n", ack);

            base = ack + 1;

        } else {

            printf("Timeout...\n");
            printf("Resending from Packet %d\n\n", base);

            next = base;
        }
    }

    printf("All packets sent successfully\n");

    close(sockfd);

    return 0;
}