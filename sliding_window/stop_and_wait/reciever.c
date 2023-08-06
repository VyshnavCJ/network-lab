#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main(int argc,char* argv[])
{
	int serv_sockfd,new_sockfd,portno,clilen,n,len1,count=0;
	struct sockaddr_in serv_addr,cli_addr;
	char buffer[256],buffer1[255]="ACKNOWLEDGEMENT",buffer2[255]="no";
	
	serv_sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(serv_sockfd<0){
		printf("error");
	}
	portno= atoi(argv[1]);
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr =INADDR_ANY;
	
	bind(serv_sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	
	listen(serv_sockfd,5);
	clilen = sizeof(cli_addr);
	new_sockfd=accept(serv_sockfd,(struct sockaddr*)&cli_addr,&clilen);
	
	bzero(buffer,256);
	n = read(new_sockfd,buffer,255);
	printf("The no is recived..!\n");
	int no= atoi(buffer);
	int i=0;
	while(1){
		n = read(new_sockfd,buffer,255);
		printf("the message is : %s\n",buffer);
		if((strcmp("3",buffer)==0) || (strcmp("5",buffer)==0)){
			if(count==0){
				sleep(3);
				n= write(new_sockfd,buffer2,255);
				printf("the ACKNOWLEDGEMENT SEND IS : %s\n",buffer2);
				count=1;
			}else{
				i++;
				count=0;
				n= write(new_sockfd,buffer1,255);
				printf("the ACKNOWLEDGEMENT SEND IS : %s\n",buffer1);
			}
		}else{
		
			n= write(new_sockfd,buffer1,255);
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
	
	//n = read(new_sockfd,buffer,255);
	//printf("the message is : %s",buffer);
	
	
	
	
	
	
}
