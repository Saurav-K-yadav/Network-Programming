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
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("Unable to create a socket");
    }

    memset(&server, 0, sizeof(server));
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // address of the server loopback for the experiment
    server.sin_family = AF_INET;
    server.sin_port = htons(20000); // taking port no 20000 for the experiment

    char str[1000];
    char mem[1000];
    int s = sizeof(server);
    int n;

    printf("Please Enter a text\n");
    bzero(str, sizeof(str));

    fgets(str, 200, stdin);
    sendto(sock, str, 200, 0, (struct sockaddr *)&server, s);

    bzero(mem, sizeof(mem));
    n = recvfrom(sock, (char *)mem, 200, 0, (struct sockaddr *)&server, &s);
    printf("Server replied: %s\n", mem);

    close(sock);
    return 0;
}
