#include "../../headers/ThreadsManipulations.hpp"
#include "../../headers/ClientServerSettings.hpp"

int main(int argc, char* argv[]){
    CustomString* customString { new CustomString };
    std::string str { " " };
    unsigned int sum {};
    ClientServerSettings server;

    tryAgain:
    server.setClientfd(socket(AF_INET, SOCK_STREAM, 0));
    if(server.getClientfd() < 0){
        server.errMsg("failed to establish the connection. Waiting for clients to connect.");

        while(true)
            if(server.getClientfd() >= 0)
                break;
    }

    std::cout << "SERVER: Socket for server was successfully created." << std::endl;

    server.server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server.server_addr.sin_port = htons(PORTNUMBER);
    server.server_addr.sin_family = AF_INET;

    if(bind(server.getClientfd(), reinterpret_cast<struct sockaddr*>(&(server.server_addr)),
            sizeof(server.server_addr)) < 0){
        server.errMsg("failed to bind the connection. Socket has already been established.");
        exit(EXIT_FAILURE);
    }

    socklen_t size { sizeof(server.server_addr) };
    if(listen(server.getClientfd(), 1) < 0){
        server.closeConnection(server.getClientfd());
    }
    std::cout << SERVERMSG << "Listening clients..." << std::endl;

    server.setServerfd(accept(server.getClientfd(),
                              reinterpret_cast<struct sockaddr*>(&(server.server_addr)), &size));
    if(server.getServerfd() < 0){
        server.errMsg("can't accept the client.");
        server.closeConnection(server.getClientfd());
    }

    char buffer[CLI_SERV_BUFFER_SIZE];
    std::cout << "To disconnect enter the \'" << CLIENT_CLOSE_CONNECTION_SYMBOL
              << "\' symbol." << std::endl;

    while(server.getServerfd() > 0){
        if(send(server.getServerfd(), buffer, CLI_SERV_BUFFER_SIZE, MSG_NOSIGNAL) < 0){
           server.closeConnection(server.getClientfd());
            goto tryAgain;
        }

        if(recv(server.getServerfd(), buffer, CLI_SERV_BUFFER_SIZE, MSG_NOSIGNAL) < 0){
            server.closeConnection(server.getClientfd());
            goto tryAgain;
        }

        str = buffer;
        sum = atoll(str.c_str());
        customString->isGreater2SymbolsAndMultipleOf32(str, sum);

        if(server.isClientConnectionClosed(buffer))
            server.setIsExitFlag(true);
    }
    server.setIsExitFlag(false);

    delete customString;
    customString = nullptr;

    return EXIT_SUCCESS;
}
