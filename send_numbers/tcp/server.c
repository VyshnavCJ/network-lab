#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#define MAX 80
#define PORT 8080
#define SA struct sockaddr
#define SAI struct sockaddr_in

void chat(int connfd){
    int num=0,con_num=0;
    while(1){
        con_num=0;
        read(connfd, &con_num, sizeof(con_num));
        printf("Client: %d\nServer: ", ntohl(con_num));
        scanf("%d",&num);
        con_num = htonl(num);
        write(connfd, &con_num, sizeof(con_num));
        if (ntohl(con_num) == 0) {
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

