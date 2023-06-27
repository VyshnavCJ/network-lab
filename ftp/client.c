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

void send_file(int sockfd){
  int n;
  char data[MAX] = {0};

  FILE *fp;
  char *filename = "send.txt";
  fp = fopen(filename,"r");

  while(fgets(data, MAX, fp) != NULL) {
    send(sockfd, data, sizeof(data), 0);
    bzero(data, MAX);
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

    send_file(sockfd);
    close(sockfd);
    return 0;
}

