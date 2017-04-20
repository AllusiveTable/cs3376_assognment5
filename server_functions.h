#define server_functions.h
//check the arguments such that there is no more than 1
void checkArg(int argc);
//initialize the socket, return its id
int initSocket();
//initialize the server address
void initServAddr(int sockfd, struct sockaddr_in serv_addr, int portno);
//initialize a child process, return its id
int initChild();
//accept the connection from the client, return its id
int acceptSocket(int sockfd, struct sockaddr_in cli_addr);
//recieve the message, print it, send confirmation to the client
void receiveMsg( int newsockfd);
//clean up the zombie processes
void cleanupChild(int signal);
//print an error and quit
void error(const char *msg);
