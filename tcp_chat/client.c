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


void palindrome(char buff[]){
    char str[MAX];
    strcpy(str,buff);
    int len=strlen(str)-1;
    int i,flag=0;
    for(i=0;i<len/2;i++)
        if(str[i]!=str[len-i-1]){
            printf("\n%s is not palindrome\n",str);
            flag=1;
            break;
        }
    if(!flag) printf("\nString is a palindrome\n");

}


void chat(int sockfd){
    char buff[MAX];
    int n;
    while(1) {
        bzero(buff, sizeof(buff)); 
        printf("Client: ");
        n = 0;
        while ((buff[n++] = getchar()) !='\n');
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
        palindrome(buff);
    }
}

int main(){
    SAI server;
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket successfully created..\n");
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);
    if (connect(sockfd, (SA*)&server, sizeof(server)) == 0) 
        printf("connected to the server..\n");

    chat(sockfd);
    close(sockfd);
    return 0;
}

