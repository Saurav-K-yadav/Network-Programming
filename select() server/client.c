#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
int main()
{
    struct sockaddr_in server;

    int sock = 0;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Unable to create a socket");
    }

    memset(&server, 0, sizeof(server));
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // address of the server loopback for the experiment
    server.sin_family = AF_INET;
    server.sin_port = htons(20000); // taking port no 20000 for the experiment

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
        printf("Failed to connect to the server");

    char str[1000];
    printf("Please Enter a text\n");
    scanf("%s", str);

    char buff[10000];

    while (1)
    {
        send(sock, str, sizeof(str), 0);
        read(sock, buff, strlen(str));
        printf("Server replied : %s\n", buff);
        break;
    }
    close(sock);
    return 0;
}
