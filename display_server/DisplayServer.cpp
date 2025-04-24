#include "DisplayServer.h"

#include <iostream>
#include <netinet/in.h>

#include "../socket/Socket.h"



[[noreturn]] void DisplayServer::start()
{
    Socket sock(AF_INET, SOCK_STREAM, 0);
    sock.BindAndListen(port);

    std::cout << "[Display server] Server listening on port " << port << "..." << std::endl;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    socklen_t addrLen = sizeof(addr);


    std::cout << "[Display server] Connecting to processing server..." << std::endl;
    while (true)
    {
        Socket clientSocket(sock.Accept(reinterpret_cast<sockaddr*>(&addr), addrLen));

        while (true)
        {
            if (std::string message = clientSocket.ReceiveString(); !message.empty())
            {
                std::cout << "[Display server] Received message: " << message << std::endl;
            } else
            {
                std::cerr << "[Display server] Received empty message" << std::endl;
            }
        }

    }
}
