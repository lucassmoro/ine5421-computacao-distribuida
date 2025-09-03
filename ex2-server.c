#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int ssocket, csocket;
    int serverlen, clientlen;
    struct sockaddr_in serveraddr, clientaddr;
    char buffer[100];
    char op;
    int a, b, resultado;

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(1100);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverlen = sizeof(serveraddr);
    
    ssocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ssocket == -1) perror("fudeu criando socket");

    bind(ssocket, (struct sockaddr*) &serveraddr, serverlen);
    if (listen(ssocket, 3) == -1) perror("error on listen");

    clientlen = sizeof(clientaddr);
    while(1){
        csocket = accept(ssocket, (struct sockaddr*) &clientaddr, &clientlen);
        // duvida de c: considerando que o buffer é uma lista de 100 char, como o programa 
        //com o sscanf consegue 'pegar os indices' corretos do vetor para atribuir as variaveis op, a, b
        read(csocket, buffer, 100);
        sscanf(buffer, "%c %d %d", &op, &a, &b);
        switch(op){
            case '+': resultado = a + b; break;
            case '-': resultado = a - b; break;
            case '*': resultado = a * b; break;
            case '/': resultado = a / b; break;
        }
        write(csocket, &resultado, 4);
    }
}