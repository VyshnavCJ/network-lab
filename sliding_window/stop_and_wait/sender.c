#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#define PORT 8080
#define MAX 1000
#define SA struct sockaddr
#define SAI struct sockaddr_in
int main(){
	int sockfd,n=0;
	char buffer[MAX];
	SAI serv_addr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr =htonl(INADDR_ANY);
	
	bzero(buffer,MAX);
	
	if((connect(sockfd,(struct sockaddr*)& serv_addr,sizeof(serv_addr)))==0)
        printf("Connected with server..\n");
	printf("Enter the no of message:");
	while((buffer[n++]=getchar())!='\n');	
	write(sockfd,buffer,MAX);
	int no= atoi(buffer);
	int i =0;
	while(1){
        bzero(buffer,MAX);	
		printf("Enter the data: ");
        n=0;
		while((buffer[n++]=getchar())!='\n');	
		write(sockfd,buffer,MAX);
		printf("the message is : %s\n",buffer);
        bzero(buffer,MAX);
		read(sockfd,buffer,MAX);
		printf("the reply is : %s\n",buffer);
		if(strcmp("ACKNOWLEDGEMENT",buffer)==0){
			i++;	
		}	
		if(i==no){
			break;
		}
	}
    close(sockfd);	
}
