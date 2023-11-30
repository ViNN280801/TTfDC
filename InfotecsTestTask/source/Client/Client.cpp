#include "../../headers/ThreadsManipulations.hpp"
#include "../../headers/ClientServerSettings.hpp"

unsigned int fistProgramFunctionality(std::string str){
    ThreadsManipulations threadManipulation;

    std::thread checkThread([&str, &threadManipulation]() {
        str = threadManipulation.checkThreadWork(str, threadManipulation);
    });
    checkThread.join();

    threadManipulation.setBuffer(str);
    unsigned int sum {};

    std::thread sumThread([&sum, &threadManipulation]() {
        sum = threadManipulation.sumThreadWork(threadManipulation);
    });
    sumThread.join();

    return sum;
}

int main(int argc, char* argv[]){
    std::string str { " " };
    ClientServerSettings client;

    tryAgain:
    client.setClientfd(socket(AF_INET, SOCK_STREAM, 0));
    if(client.getClientfd() < 0)
        std::cout << CLIENTERRMSG << "failed to establish the connection." << std::endl;


    client.server_addr.sin_port = htons(PORTNUMBER);
    client.server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IPV4, &(client.server_addr.sin_addr));

    std::cout << "Client socket was successfully created." << std::endl;

    if(connect(client.getClientfd(), reinterpret_cast<struct sockaddr*>(&(client.server_addr)),
               sizeof(client.server_addr)) < 0){
        client.errMsg("failed to connect. Waiting for the client to connect to the server...");

        while(true)
            if(connect(client.getClientfd(), reinterpret_cast<struct sockaddr*>(&(client.server_addr)),
                       sizeof(client.server_addr)) >= 0)
                break;

    }
    else if(connect(client.getClientfd(), reinterpret_cast<struct sockaddr*>(&(client.server_addr)),
                    sizeof(client.server_addr)) == 0)
        std::cout << "Connection to server " << inet_ntoa(client.server_addr.sin_addr)
                  << " with port: " << PORTNUMBER << std::endl;

    char buffer[CLI_SERV_BUFFER_SIZE];
    recv(client.getClientfd(), buffer, CLI_SERV_BUFFER_SIZE, 0);

    while(true){
        std::cout << "Enter a string: ";
        std::cin.getline(buffer, CLI_SERV_BUFFER_SIZE);
        str = buffer;
        client.setSum(fistProgramFunctionality(str));
        str = std::to_string(client.getSum());

        if(send(client.getClientfd(), str.c_str(), str.length(), MSG_NOSIGNAL) < 0){
            client.closeConnection(client.getClientfd());
            goto tryAgain;
        }

        if(client.isClientConnectionClosed(buffer))
            break;
    }
    close(client.getClientfd());

    return EXIT_SUCCESS;
}
