#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int queue_socket, server_socket;
    struct sockaddr_un server_addresss, client_address;
    char ch = 'A';
    socklen_t client_len, server_len;
    //char buffer[100];
    //char* iterador = buffer;

    queue_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    strcpy(server_addresss.sun_path, "pauduro");
    server_addresss.sun_family = AF_UNIX;
    server_len = sizeof(server_addresss);
    unlink("pauduro");
    bind(queue_socket, (struct sockaddr*) &server_addresss, server_len);
    listen(queue_socket, 10);

    server_len = sizeof(server_addresss);
    while(1){
        printf("esperando requisicao");
        fflush(stdout);
        client_len = sizeof(client_address);
        server_socket = accept(queue_socket, (struct sockaddr*) &client_address, &client_len);
        read(server_socket, &ch, sizeof(ch));
        ch++;
        write(server_socket, &ch, sizeof(ch));

        close(server_socket);
    }
    close(queue_socket);
}