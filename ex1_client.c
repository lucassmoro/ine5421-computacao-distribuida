#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int sockfd;
    struct sockaddr_in sockfdaddr;
    char msg = 'A';
    int len;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    sockfdaddr.sin_family = AF_INET;
    sockfdaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockfdaddr.sin_port = htons(1100);
    len = sizeof(sockfdaddr);
    int result = connect(sockfd, (struct sockaddr*)&sockfdaddr, len);
    if (result == -1){
        perror("fudeu");
        exit(1);
    }
    write(sockfd, &msg, 1);
    read(sockfd, &msg, 1);
    printf("cliente enviando %c", msg);
    close(sockfd);
    exit(0);

}