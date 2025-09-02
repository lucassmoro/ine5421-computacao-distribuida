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
    char msg[] = "sexo";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int len;
    char* palavra = msg;
    
    sockfdaddr.sin_family = AF_INET;
    sockfdaddr.sin_addr.s_addr = inet_addr("192.168.171.165");
    sockfdaddr.sin_port = htons(1100);
    len = sizeof(sockfdaddr);

    int result = connect(sockfd, (struct sockaddr*)&sockfdaddr, len);
        if (result == -1){
            perror("fudeu");
            exit(1);
        }
    while(1){
        write(sockfd, palavra, 1);
        printf("cliente enviando %c\n", *palavra);
        sleep(1);
        read(sockfd, palavra, 1);
        palavra++;
    }
    close(sockfd);
    exit(0);

}