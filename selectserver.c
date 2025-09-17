#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#define STDIN 0
#define PORT 6000
int main(){
    int listen_socket, accept_socket;
    int listen_len, accept_len;
    struct sockaddr_in listen_address, accept_address;
    socklen_t accept_size;

    char ch;

    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    listen_address.sin_family = AF_INET;

    listen_address.sin_addr.s_addr = htonl(INADDR_ANY);
    listen_address.sin_port = htons(PORT);
    listen_len = sizeof(listen_address);

    bind(listen_socket, (struct sockaddr*)&listen_address,listen_len);
    listen(listen_socket, 5);

    fd_set current_sockets, ready_sockets;
    FD_ZERO(&current_sockets);
    FD_SET(listen_socket, &current_sockets);
    
    while(1){
        ready_sockets = current_sockets;
        if(select(STDIN+1,&ready_sockets,NULL,NULL,NULL) < 0){
            perror("deu merda");
            exit(1);
        } 
        for (int i = 0; i<FD_SETSIZE; i++){
            if (FD_ISSET(i, &ready_sockets)){
                if (i == listen_socket) {
                    //aqui temos um novo socket conectado (nao estava antes)
                    accept_size = sizeof(accept_address);
                    accept_socket = accept(listen_socket, (struct sockaddr*)&accept_address, &accept_size);
                    printf("Novo cliente conectado\n");
                } else{
                    //conexao de socket ja conectado
                    char buffer[1024];
                    int n = read(i, &buffer, sizeof(buffer));
                    if (n<=0){
                        //desconectou ou deu problema
                        FD_CLR(i, &current_sockets); //remove do set, agora ele caso se conecte dnv vai receber outro descritor pelo accept()
                    } else {
                        FD_SET(i, &current_sockets);
                        buffer[n] = '\0';
                        write(i, buffer, n);
                    }
                } 
            }
        }
    }
    return 0;
}
