#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr
#define SAI struct sockaddr_in

void chat(int connfd){
    int n;
    n =0;
    time_t currentTime = time(NULL);
    char *buff = ctime(&currentTime);
    write(connfd, buff, strlen(buff));
}

int main(){
    SAI server,client;
    // socket create
    int sockfd, connfd, len;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket successfully created.....\n");
    // server init
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

