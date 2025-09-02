#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int serversocket, clientsocket;
    //socklen_t 
    int server_len, client_len;
    struct sockaddr_in server_addr, client_addr;
    char msg[100];
    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("192.168.171.165");
    server_addr.sin_port = htons(1100);

    server_len = sizeof(server_addr);
    if (bind(serversocket, (struct sockaddr *)&server_addr, server_len) == -1) {
        perror("bind");
        exit(1);
    }
    listen(serversocket, 5);
        
    client_len = sizeof(client_addr);
    // aceita conexao com um socket so e fica recebendo coisa dele
    clientsocket = accept(serversocket, (struct sockaddr*)&client_addr, &client_len); 
    while(1){
        read(clientsocket, &msg, 5);
        printf("recebendo %s e enviando de volta\n", msg);
        sleep(1);
        write(clientsocket, &msg, 5);
    }
    close(clientsocket);
}