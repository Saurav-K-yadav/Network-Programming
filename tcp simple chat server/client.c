#include <sys/types.h>
#include<arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
    char sendline[100];
    char recvline[100];

    int sockfd, n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof servaddr);
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
   
    while (1)
    {
        bzero(sendline, 100);
        printf("message to send:\n");
        fgets(sendline, 100, stdin);
        send(sockfd, sendline, strlen(sendline), 0);

        bzero(recvline, 100);
        recv(sockfd, recvline, 100, 0);
        printf("received: ");
        printf("%s", recvline);
    }
    return 0;
}