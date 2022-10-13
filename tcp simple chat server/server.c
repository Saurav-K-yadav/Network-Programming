#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int listen_fd, comm_fd;

    char str[100];
    
    struct sockaddr_in servaddr;
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(22000);
    
    bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    listen(listen_fd, 10);

    char sendline[1000];

    comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);
    while (1)
    {
        bzero(str, 100);
        printf("received:\n");
        recv(comm_fd, str, 100, 0);
        printf("%s",str);

        bzero(sendline, 100);
        printf("send: \t");
        fgets(sendline, 100, stdin);
        send(comm_fd, sendline, strlen(sendline), 0);
    }
    
    close(comm_fd);
    return 0;
}