#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <cctype>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVERMSG "SERVER: "
#define SERVERERRMSG "SERVER ERROR: "
#define CLIENTERRMSG "CLIENT ERROR: "
#define PORTNUMBER 1500
#define CLI_SERV_BUFFER_SIZE 1024
#define CLIENT_CLOSE_CONNECTION_SYMBOL '#'

#define SERVER_IPV4 "127.0.0.1"

class ClientServerSettings{
private:
    int serverfd, clientfd;
    bool isExitFlag;
    unsigned int sum;

public:
    struct sockaddr_in server_addr;

    ClientServerSettings() {};
    virtual ~ClientServerSettings() {};

    inline int getServerfd() { return this->serverfd; }
    inline void setServerfd(int newServerfd) { this->serverfd = newServerfd; }
    inline int getClientfd() { return this->clientfd; }
    inline void setClientfd(int newClientfd) { this->clientfd = newClientfd; }
    inline bool getIsExitFlag() { return this->isExitFlag; }
    inline void setIsExitFlag(bool newFlagValue) { this->isExitFlag = newFlagValue; }
    inline unsigned int getSum() { return this->sum; }
    inline void setSum(unsigned int newSum) { this->sum = newSum; }

    inline void errMsg(const char* str){
        std::cout << SERVERERRMSG << str << std::endl;
    }

    inline bool isClientConnectionClosed(const char* msg){
        for(size_t i = 0; i < strlen(msg); i++){
            if(*(msg + i) == CLIENT_CLOSE_CONNECTION_SYMBOL){
                return true;
            }
        }
        return false;
    }

    inline void closeConnection(int fd){
        close(fd);
        std::cout << SERVERMSG << "Connection has been closed." << std::endl;
    }
};
