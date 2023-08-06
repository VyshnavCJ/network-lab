#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

#define SA struct sockaddr
#define SAI struct sockaddr_in
#define PORT 8080
#define MAX 1000

int main()
{
	int sockfd,connfd,len,n,len1,count=0;
	SAI serv_addr,cli_addr;
	char buffer[MAX],buffer1[MAX]="ACKNOWLEDGEMENT",buffer2[MAX]="no";
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr =INADDR_ANY;
	
	bind(sockfd,(SA*)&serv_addr,sizeof(serv_addr));
	
	listen(sockfd,5);
	len = sizeof(cli_addr);
    connfd=accept(sockfd,(struct sockaddr*)&cli_addr,(socklen_t*)&len);
	
	bzero(buffer,MAX);
	read(connfd,buffer,MAX);
	printf("The no is recived..!\n");
	int no= atoi(buffer);
	int i=0;
	while(1){
        bzero(buffer,MAX);
		read(connfd,buffer,MAX);
		printf("the message is : %s\n",buffer);
		if((strcmp("3",buffer)==0) || (strcmp("5",buffer)==0)){
			if(count==0){
				sleep(3);
				write(connfd,buffer2,MAX);
				printf("the ACKNOWLEDGEMENT SEND IS : %s\n",buffer2);
				count=1;
			}else{
				i++;
				count=0;
				write(connfd,buffer1,MAX);
				printf("the ACKNOWLEDGEMENT SEND IS : %s\n",buffer1);
			}
		}else{
		
			write(connfd,buffer1,MAX);
			printf("the ACKNOWLEDGEMENT SEND IS : %s\n",buffer1);
			i++;
			if(i==no){
				break;
			}
		}
		if(i==no){
				break;
		}
		
	}
 close(sockfd);	
}
