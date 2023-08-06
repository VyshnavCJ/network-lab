#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(int argc,char * argv[] ){
	int sockfd,portno,n;
	char buffer[255],buffer1[255];
	struct sockaddr_in serv_addr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	portno = atoi(argv[1]);
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr =INADDR_ANY;
	//printf("%d",portno);
	
	bzero(buffer,255);
	bzero(buffer1,255);
	
	connect(sockfd,(struct sockaddr*)& serv_addr,sizeof(serv_addr));
	printf("Enter the no of message:");
	scanf("%s",buffer);
	n = write(sockfd,buffer,255);
	int no= atoi(buffer);
	int i =0;
	while(1){
	
		printf(" enter the data ");
		scanf("%s",buffer);
		
	
		n = write(sockfd,buffer,255);
		printf("the message is : %s\n",buffer);
		n = read(sockfd,buffer1,255);
		printf("the reply is : %s\n",buffer1);
		if(strcmp("ACKNOWLEDGEMENT",buffer1)==0){
			i++;
			
		}
		
		if(i==no){
			break;
		}
	}
	
	n = read(sockfd,buffer1,255);
}
