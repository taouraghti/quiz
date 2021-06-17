#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include<pthread.h>
#include "./getnextline/get_next_line.h"
#include <fcntl.h>

typedef struct User
{
    char username[30];
    int score;
}User;

typedef struct SocketQst
{
    char **qst;
    int socketClient;
}SocketQst;

char **tabRep;

int countNumberOfline(char *file)
{
    int i = 0;
    char	*line;
    int fd = open(file, O_RDONLY);
    while(get_next_line(fd, &line) > 0)
    {
        i++;
        free(line);
		line = NULL;
    }
    i++;
    close(fd);
    return i;
}

char**		read_from_file(int fd,char **qst)
{
	char	*line;
	int n = 1;
    int i = 0;
	while (n > 0)
	{
		n = get_next_line(fd, &line);
		if (n != -1)
		{
			qst[i] = strdup(line);
			free(line);
			line = NULL;
            i++;
		}
	}
    qst[i] = NULL;
	return (qst);
}


int checkRep(char *rep, int i)
{
    if (strcmp(rep,tabRep[i]))
        return 0;
    return 1;
}


void *function(void *arg)
{
    SocketQst socket = *(SocketQst *)arg;
    char rep[128];
    int i = 0;
    int result = 0;

    char *qst = strdup("quel est votre nom ?");
    User user;
    send(socket.socketClient, qst, strlen(qst) + 1, 0);
    recv(socket.socketClient, &user, sizeof(user), 0);
    printf("vous etes: %s\n", user.username);

    while(1)
    {
        if(socket.qst[i] == NULL)
            break;
        //char *qst = strdup(socket.qst[0]);
        send(socket.socketClient, socket.qst[i], strlen(socket.qst[i]) + 1, 0);
        int r = recv(socket.socketClient, &rep, sizeof(char) * 2, 0);
        printf("votre reponse %c\n", *rep);
        //free(qst);
        result += checkRep(rep, i);
        printf("%d\n", r);
        i++;
    }
    printf("votre resultat est: %d\n", result);
     close(socket.socketClient);
    
    pthread_exit(NULL);
}


int main(int ac, char **av)
{
    int fd;
    SocketQst socketQst;

   /*-------------- read qst ---------------*/
    int numberOfline = countNumberOfline(av[1]);

    if ((fd = open(av[1], O_RDONLY)) < 0)
		exit(-1);
	else
	{
        socketQst.qst = (char**)malloc(sizeof(char *) * (numberOfline + 1));
		socketQst.qst = read_from_file(fd, socketQst.qst);
		close(fd);
	}
/*------------------------------------*/

/*-------------- read rep ---------------*/

    numberOfline = countNumberOfline(av[2]);

    if ((fd = open(av[2], O_RDONLY)) < 0)
		exit(-1);
	else
	{
        tabRep = (char**)malloc(sizeof(char *) * (numberOfline + 1));
		tabRep = read_from_file(fd,  tabRep);
		close(fd);
	}


/*------------------------------------*/
    int socketServer = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrServer;
    addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(30000);

    int opt = 1;
    int r = setsockopt(socketServer, SOL_SOCKET, SO_REUSEADDR, &opt,
                     sizeof(opt));

    if (bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer)) < 0)
        printf("bind failed\n");
    printf("bind: %d\n", socketServer);

    listen(socketServer, 5);
    printf("listen\n");

    pthread_t clientThread[3];
    for(int i = 0; i < 3; i++)
    {
        //num = i;
        struct sockaddr_in addrClient;
        socklen_t csize = sizeof(addrClient);
        int socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);
        printf("accept\n");
        printf("client: %d\n", socketClient);

        socketQst.socketClient = socketClient;
        pthread_create(&clientThread[i], NULL, function, &socketQst);
    }
    for(int i = 0; i < 3; i++)
    {
        pthread_join(clientThread[i], NULL);
    }
    close(socketServer);
    printf("close\n");
    return 0;
}