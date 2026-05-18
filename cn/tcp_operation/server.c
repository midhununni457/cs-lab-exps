#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    int sockfd, newsock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    char buffer[1024];
    char result[1024];

    int num1, num2, ans;
    char op;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    listen(sockfd, 3);

    printf("Waiting for connections...\n");

    newsock = accept(sockfd, (struct sockaddr *)&client, &len);

    read(newsock, buffer, sizeof(buffer));

    sscanf(buffer, "%d %c %d", &num1, &op, &num2);
    printf("Received expression: %d %c %d\n", num1, op, num2);

    switch (op)
    {
    case '+':
        ans = num1 + num2;
        break;
    
    case '-':
        ans = num1 - num2;
        break;

    case '*':
        ans = num1 * num2;
        break;

    case '/':
        ans = num1 / num2;
        break;
    
    default:
        sprintf(result, "Invalid operator");
        send(newsock, result, sizeof(result), 0);

        close(newsock);
        close(sockfd);
        
        break;
    }
    sprintf(result, "Result = %d", ans);

    send(newsock, result, sizeof(result), 0);

    printf("Result sent to client. Closing connection...\n");

    close(newsock);
    close(sockfd);

    return 0;
}