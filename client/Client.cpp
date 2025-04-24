#include "Client.h"
#include <string>
#include <cstring>
#include <thread>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "../socket/Socket.h"

void Client::start() {
    Socket sock(AF_INET, SOCK_STREAM, 0);
    if (!sock.ConnectTo(ip, port))
    {
        throw std::runtime_error("Failed to connect to server");
    }

    std::cout << "Connected to server at " << ip << ":" << port << std::endl;
    std::cout << "Enter messages: " << std::endl;

    std::string inputString;
    while (std::getline(std::cin, inputString))
    {
        if (inputString.empty()) { continue; }


        if (!sock.SendString(inputString))
        {
            throw std::runtime_error("Failed to send message");
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << sock.ReceiveString() << std::endl;
    }
}
