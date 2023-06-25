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

void chat(int sockfd,SAI client){
    printf("\nServer ready,waiting for client....\n");
    char buff[MAX];
    int n,len = sizeof(client);
    while(1)
    {      
        bzero(buff, sizeof(buff));
        recvfrom(sockfd,buff,sizeof(buff),0,(SA*)&client,(socklen_t*)&len);
        printf("\nClient:%s",buff);
        n = 0; 
        printf("\nServer:");
        bzero(buff, sizeof(buff)); 
        while ((buff[n++] = getchar()) !='\n');
        sendto(sockfd,buff,sizeof(buff),0,(SA*)&client,len);
        if(strncmp(buff,"exit",4)==0){
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

