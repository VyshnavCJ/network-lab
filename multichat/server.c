#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

pthread_mutex_t mutex;
int clients[20];
int n=0;

void sendtoall(char *msg,int curr){
	int i;
	pthread_mutex_lock(&mutex);
	for(i = 0; i < n; i++) {
		if(clients[i] != curr) {
			send(clients[i],msg,strlen(msg),0);
		}
	}
	pthread_mutex_unlock(&mutex);
}

void *recvmg(void *client_sock){
	int sock = *((int *)client_sock);
	char msg[500];
	int len;
	while((len = recv(sock,msg,500,0)) > 0) {
		msg[len] = '\n';
		sendtoall(msg,sock);
	}
    return NULL;
	
}

int main(){
	struct sockaddr_in ServerIp;
	pthread_t recvt;
	int sockfd=0 , connfd=0;
	
	ServerIp.sin_family = AF_INET;
	ServerIp.sin_port = htons(8080);
	ServerIp.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockfd = socket( AF_INET , SOCK_STREAM, 0 );
	if( bind( sockfd, (struct sockaddr *)&ServerIp, sizeof(ServerIp)) == 0 )
		printf("Server Started\n");
		
	if( listen( sockfd ,20 ) == 0 )
		printf("listening \n");
		
	while(1){
		if( (connfd = accept(sockfd, (struct sockaddr *)NULL,NULL)) < 0 )
			printf("accept failed  \n");
		pthread_mutex_lock(&mutex);
		clients[n]= connfd;
		n++;
		// creating a thread for each client 
		pthread_create(&recvt,NULL,(void *)recvmg,&connfd);
		pthread_mutex_unlock(&mutex);
	}
	return 0; 
	
}
