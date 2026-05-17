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

    int acked[TOTAL_PACKETS + 1] = {0};

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    printf("Connected to server\n\n");

    // Timeout = 3 sec
    tv.tv_sec = 3;
    tv.tv_usec = 0;

    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,
               (const char *)&tv, sizeof(tv));

    int base = 1;

    while (base <= TOTAL_PACKETS) {

        // Send all packets in window
        for (int i = base;
             i < base + WINDOW_SIZE &&
             i <= TOTAL_PACKETS;
             i++) {

            if (acked[i] == 0) {

                sprintf(packet, "%d", i);

                printf("Sending Packet %d\n", i);

                send(sockfd, packet, strlen(packet), 0);
            }
        }

        // Receive ACKs
        for (int i = base;
             i < base + WINDOW_SIZE &&
             i <= TOTAL_PACKETS;
             i++) {

            memset(buffer, 0, sizeof(buffer));

            int n = read(sockfd, buffer, sizeof(buffer));

            if (n > 0) {

                int ack = atoi(buffer);

                acked[ack] = 1;

                printf("ACK received for Packet %d\n", ack);
            }
        }

        printf("\n");

        // Slide window
        while (acked[base] == 1)
            base++;
    }

    printf("All packets sent successfully\n");

    close(sockfd);

    return 0;
}