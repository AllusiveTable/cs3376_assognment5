#define client_functions.h

void error(const char *msg);
void checkArg(int argc,char *argv[]);
int initSocket();
void initServer(struct hostent *server, char *argv[]);
void initServAddr(struct hostent *server,struct sockaddr_in serv_addr, int portno);
void connectToServer(int sockfd, struct sockaddr_in serv_addr);
void sendMsg(int sockfd);
void receiveMsg(int sockfd);