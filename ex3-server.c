#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    int serversocket;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t server_len, client_len;
    int buffer[2];
    int recebidos;
    int qtd = 0;
    
    serversocket = socket(AF_INET, SOCK_DGRAM, 0);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(6000);

    server_len = sizeof(serveraddr);
    if (bind(serversocket, (struct sockaddr *) &serveraddr, server_len) < 0) {
        perror("Bind failed"); close(serversocket); exit(1) ;
    } 

    client_len = sizeof(clientaddr);
    time_t tempo = time(NULL);
    time_t tempo_dif;
    while(1){
        int n = recvfrom(serversocket, &recebidos, sizeof(recebidos), 0, (struct sockaddr *) &clientaddr, &client_len);
        if (n>0) qtd++;
        buffer[0] += recebidos;
        if (((tempo_dif = time(NULL)) - tempo) > 1) {
            printf("SERVER: qtd de medicoes coletadas = %d\n", qtd);
            printf("SERVER: soma das medicoes = %d\n", buffer[0]);
            tempo = time(NULL);
        }
    }
    close(serversocket);
    return 0;
}