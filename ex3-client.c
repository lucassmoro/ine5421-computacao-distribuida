#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int sockfd;
    struct sockaddr_in sockfdaddr;
    int numero;

    sockfdaddr.sin_family = AF_INET;
    sockfdaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockfdaddr.sin_port = htons(6000);
    socklen_t len = sizeof(sockfdaddr);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    while(1){
        numero = rand();
        sendto(sockfd, &numero, sizeof(numero), MSG_CONFIRM, (struct sockaddr*)&sockfdaddr, sizeof(sockfdaddr));
        //int n = recvfrom();
    }
    close(sockfd);
    return 0;
    
}