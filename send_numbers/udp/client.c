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

void chat(int sockfd,SAI server){
    printf("\nClient ready....\n");
    int n,len=sizeof(server);
    while(1)
    {      
        printf("\nClient:");
        n = 0;
        scanf("%d",&n);
        sendto(sockfd,&n,sizeof(n),0,(SA*)&server,len);
        n=0;
        recvfrom(sockfd,&n,sizeof(n),0,(SA*)&server,(socklen_t*)&len);
        printf("\nServer:%d\n",n);
        if(n==0){
            printf("Client Exit...\n");
            break;
        }
    }

}
int main(){
    SAI server;
    int sockfd;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    server.sin_port=htons(PORT);

    chat(sockfd,server);
    close(sockfd);
	return 0;
}

