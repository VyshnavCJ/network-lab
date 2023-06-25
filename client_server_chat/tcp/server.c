#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define MAX 80
#define PORT 8080
#define SA struct sockaddr
#define SAI struct sockaddr_in

void chat(int connfd){
    char buff[MAX];
    int n;
    while(1){
        bzero(buff, MAX);
        read(connfd, buff, sizeof(buff));
        printf("Client: %sServer: ", buff);
        bzero(buff, MAX);
        n =0;
        while ((buff[n++] = getchar()) != '\n');
        write(connfd, buff, sizeof(buff));
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}

int main(){
    SAI server,client;
    // socket create
    int sockfd, connfd, len;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket successfully created.....\n");
    // server init
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);
    //binding
    if ((bind(sockfd, (SA*)&server, sizeof(server))) == 0) 
        printf("Socket successfully binded..\n");
    //listening
    if ((listen(sockfd, 5)) == 0) 
        printf("Server listening..\n");
    //accept request
    len = sizeof(client);
    connfd = accept(sockfd, (SA*)&client, (socklen_t*)&len);
    printf("Server accept the client...\n");

    chat(connfd);
    close(sockfd);
    return 0;
}

