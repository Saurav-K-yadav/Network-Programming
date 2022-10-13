#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int main()
{

    int sock = 0;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Unable to create a socket");
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(20000); // taking port no 20000 for the experiment

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Unable to bind the socket");
    }

    if (listen(sock, 10) < 0)
    {
        printf("Unable to listen to the program");
    }

    // UDP
    int udpfd;
    fd_set rset;
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(udpfd, (struct sockaddr *)&server, sizeof(server));
    FD_ZERO(&rset);

    int maxfd1;
    maxfd1 = MAX(sock, udpfd) + 1;
    int nready;
    socklen_t len;
    struct sockaddr_in cliaddr;
    int cli;
    pid_t childpid;
    char inp[1000];
    for (;;)
    {
        // set listenfd and udpfd in readset
        FD_SET(sock, &rset);
        FD_SET(udpfd, &rset);
        // select the ready descriptor
        nready = select(maxfd1, &rset, NULL, NULL, NULL);
        // if tcp socket is readable then handle
        // it by accepting the connection
        if (FD_ISSET(sock, &rset))
        {
            len = sizeof(cliaddr);
            cli = accept(sock, (struct sockaddr *)&cliaddr, &len);
            if ((childpid = fork()) == 0)
            {
                close(sock);
                bzero(inp, sizeof(inp));
                read(cli, inp, sizeof(inp));
                printf("\nMessage from TCP client: ");
                printf("%s", inp);

                char temp;
                int j = strlen(inp) - 1;
                for (int i = 0; i < j; i++, j--)
                {
                    temp = inp[i];
                    inp[i] = inp[j];
                    inp[j] = temp;
                }

                printf("\nreplying : %s\n", inp);

                send(cli, inp, strlen(inp), 0);

                exit(0);
            }
            close(cli);
            printf("\nWaiting for the connection\n");
        }
        if (FD_ISSET(udpfd, &rset))
        {
            int n;
            len = sizeof(cliaddr);
            bzero(inp, sizeof(inp));
            printf("\nMessage from UDP client: ");
            n = recvfrom(udpfd, inp, sizeof(inp), 0,
                         (struct sockaddr *)&cliaddr, &len);

            puts(inp);
            char temp;
            int j = strlen(inp) - 1;
            for (int i = 0; i < j; i++, j--)
            {
                temp = inp[i];
                inp[i] = inp[j];
                inp[j] = temp;
            }

            printf("replying : %s\n", inp);

            sendto(udpfd, (const char *)inp, sizeof(inp), 0,
                   (struct sockaddr *)&cliaddr, sizeof(cliaddr));
            printf("\nWaiting for the connection\n");
        }
    }
}