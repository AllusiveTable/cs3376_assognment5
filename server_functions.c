#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "server_functions.h"
//check the arguments such that there is no more than 1
void checkArg(int argc)
{
    if (argc < 2) 
    {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
}
//initialize the socket, return its id
int initSocket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    return sockfd;
}
//initialize the server address
void initServAddr(int sockfd, struct sockaddr_in serv_addr, int portno)
{
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
}
//initialize a child process, return its id
int initChild()
{
    int pid = fork();
    if(pid < 0)
        error("ERROR on fork");
    return pid;
}
//accept the connection from the client, return its id
int acceptSocket(int sockfd, struct sockaddr_in cli_addr)
{
    socklen_t clilen = sizeof(cli_addr);
    int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) 
        error("ERROR on accept");
    return newsockfd;
}
//recieve the message, print it, send confirmation to the client
void receiveMsg(int newsockfd)
{
    char buffer[256];
    bzero(buffer,256);
    int n = read(newsockfd,buffer,255);
    if (n < 0) 
        error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);
    n = write(newsockfd,"I got your message",18);
    if (n < 0) 
        error("ERROR writing to socket");
}
//clean up the zombie processes
void cleanupChild(int signal)
{
    wait();
}
//print an error and quit
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
