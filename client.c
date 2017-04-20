#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "client_functions.h"



int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    
    checkArg(argc, argv);
    sockfd = initSocket();
    initServer(server, argv);
    initServAddr(server, serv_addr, atoi(argv[2]));
    connectToServer(sockfd, serv_addr);
    sendMsg(sockfd);
    receiveMsg(sockfd);
    close(sockfd);
    return 0;
}
