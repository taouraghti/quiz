#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

typedef struct User
{
    char username[30];
    int score;
}User;

int main()
{
    int socketClient = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrClient;
    addrClient.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrClient.sin_family = AF_INET;
    addrClient.sin_port = htons(30000);

    connect(socketClient, (const struct sockaddr *)&addrClient, sizeof(addrClient));
    printf("connect\n");

    User user;
    char *qst;
    char rep[2];
    qst = malloc(sizeof(char)*33);
    int i=0;
    recv(socketClient, qst, 33, 0);
    printf("%s\n", qst);
    scanf("%s", user.username);
    user.score = 0;
    send(socketClient, &user, sizeof(user), 0);
    while(1)
    {
        int r = recv(socketClient, qst, 33, 0);
        if (!r)
        {
            printf("Finish\n");
            break;
        }
        printf("%s\n", qst);
        scanf("%s", rep);
        send(socketClient, &rep, sizeof(rep), 0);
    }
    
     
    

    close(socketClient);
    printf("close\n");
    return 0;
}