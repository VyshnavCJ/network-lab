#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

char msg[500];

#define MAX 80
#define PORT 8080
#define SA struct sockaddr
#define SAI struct sockaddr_in

void *recvmg(void *my_sock){
	int sock = *((int *)my_sock);
	int len;
	// client thread always ready to receive message
	while((len = recv(sock,msg,500,0)) > 0) {
		msg[len] = '\n';
		fputs(msg,stdout);
	}
    return NULL;
}


int main(){
	pthread_t recvt;
	int sockfd;
	char send_msg[500];
	SAI server;
	char client_name[100];
    printf("Enter the client name: ");
    scanf("%s",client_name);
	sockfd = socket( AF_INET, SOCK_STREAM,0);
	server.sin_port = htons(PORT);
	server.sin_family= AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if( (connect( sockfd ,(struct sockaddr *)&server,sizeof(server))) == 0 )
		printf("Connected\n");
	
	//creating a client thread which is always waiting for a message
	pthread_create(&recvt,NULL,(void *)recvmg,&sockfd);
	
	//ready to read a message from console
	while(fgets(msg,500,stdin) > 0) {
		strcpy(send_msg,client_name);
		strcat(send_msg,":");
		strcat(send_msg,msg);
		write(sockfd,send_msg,strlen(send_msg));
	}
	
	//thread is closed
	pthread_join(recvt,NULL);
	close(sockfd);
	return 0;
}
