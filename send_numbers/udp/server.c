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

void chat(int sockfd,SAI client){
    printf("\nServer ready,waiting for client....\n");
    int n,len = sizeof(client);
    while(1)
    {      
        n=0;
        recvfrom(sockfd,&n,sizeof(n),0,(SA*)&client,(socklen_t*)&len);
        printf("\nClient:%d",n);
        n = 0; 
        printf("\nServer:");
        n=0;
        scanf("%d",&n);
        sendto(sockfd,&n,sizeof(n),0,(SA*)&client,len);
        if(n==0){
            printf("Server Exit...\n");
            break;
        }
    }

}

int main(){
    SAI server,client;
    int sockfd;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    server.sin_port=htons(PORT);
    if ((bind(sockfd, (SA*)&server, sizeof(server))) == 0) 
        printf("Socket successfully binded..\n");

    chat(sockfd,client);
	return 0;
 
}

