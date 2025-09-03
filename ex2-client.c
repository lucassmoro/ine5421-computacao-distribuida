#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int sockfd, len;
    struct sockaddr_in sockfdaddr;
    int operando1, operando2, resultado;
    operando1 = 1, operando2 = 2;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) perror("fudeu criando socket");
    int result;
    char buffer[100];

    snprintf(buffer, sizeof(buffer), "+ %d %d", operando1, operando2);

    sockfdaddr.sin_family = AF_INET;
    sockfdaddr.sin_port = htons(1100);
    sockfdaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    len = sizeof(sockfdaddr);
    result = connect(sockfd, (struct sockaddr*) &sockfdaddr, len);
    if (result == -1){
        perror("fudeu");
        exit(1);
    }
    write(sockfd, buffer, strlen(buffer) + 1);
    read(sockfd, &resultado, 4);
    printf("CLIENT: recebi %d\n", resultado);
    close(sockfd);
}