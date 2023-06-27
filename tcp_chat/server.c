#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr
#define SAI struct sockaddr_in

void low_up(char buff[]){
    char str[MAX],temp[MAX]; int len;
		strcpy(str,buff);
		len = strlen(str)-1;
        int i;
		for(i=0;i<len;i++)
		{
			if(islower(str[i]))
				str[i]=toupper(str[i]);
			else if(isupper(str[i]))
				str[i]=tolower(str[i]);
		}
		printf("\nThe inverted case buffer is:%s\nThe number of characters is %d\n",str,len);

}
void chat(int connfd){
    char buff[MAX];
    int n;
    while(1){
        bzero(buff, MAX);
        read(connfd, buff, sizeof(buff));
        low_up(buff);
        printf("Server: ");
        bzero(buff, MAX);
        n =0;
        while ((buff[n++] = getchar()) != '\n');
        write(connfd, buff, sizeof(buff));
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}

int main(){
    SAI server,client;
    int sockfd, connfd, len;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket successfully created.....\n");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);
    if ((bind(sockfd, (SA*)&server, sizeof(server))) == 0) 
        printf("Socket successfully binded..\n");
    if ((listen(sockfd, 5)) == 0) 
        printf("Server listening..\n");
    len = sizeof(client);
    connfd = accept(sockfd, (SA*)&client, (socklen_t*)&len);
    printf("Server accept the client...\n");

    chat(connfd);
    close(sockfd);
    return 0;
}

