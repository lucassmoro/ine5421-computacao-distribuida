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
    char msg;

    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(1100);

    server_len = sizeof(server_addr);
    bind(serversocket, (struct sockaddr *)&server_addr, server_len);
    listen(serversocket, 1);
        
    client_len = sizeof(client_addr);
    clientsocket = accept(serversocket, (struct sockaddr*)&client_addr, &client_len);
    read(clientsocket, &msg, 1);
    printf("recebendo %c e enviando de volta", msg);
    write(clientsocket, &msg, 1);
    close(clientsocket);
    
}