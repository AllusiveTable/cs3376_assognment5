/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include "server_functions.h"

int main(int argc, char *argv[])
{
     //Set up variables and check arguments
     int sockfd, newsockfd, n;
     struct sockaddr_in serv_addr, cli_addr;
     checkArg(argc);
     //Handle Zombie Processes
     signal(SIGCHLD,cleanupChild);

     //initialize socket and server address and begin listening
     sockfd = initSocket();
     initServAddr(sockfd, serv_addr, atoi(argv[1]));
     listen(sockfd,5);

     //start an infinite loop to take connections
     while(true)
     {
     /* take a connection
      * start a child process 
      * recieve the message 
      * close the new socket
      */
         newsockfd = acceptSocket(sockfd, cli_addr);
         int pid = initChild();
         if (pid == 0)
	 {
             close(sockfd);
             receiveMsg(newsockfd);

             exit(0);
         }
	 else
             close(newsockfd);
     }
     //end while
}
