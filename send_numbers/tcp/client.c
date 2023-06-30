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

void chat(int sockfd){
    char buff[MAX];
    int n,num,con_num;
    while(1) {
        printf("Client: ");
        scanf("%d",&num);
        con_num = htonl(num);
        write(sockfd, &con_num, sizeof(con_num));
        con_num=0;
        read(sockfd, &con_num, sizeof(con_num));
        printf("Server: %d", ntohl(con_num));
        if (ntohl(con_num) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main(){
    SAI server;
    //socket create
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket successfully created..\n");
    //client init
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);
    //connect with server
    if (connect(sockfd, (SA*)&server, sizeof(server)) == 0) 
        printf("connected to the server..\n");

    chat(sockfd);
    close(sockfd);
    return 0;
}

