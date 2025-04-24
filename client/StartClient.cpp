#include "Client.h"
#include "../socket/Socket.h"

int main(int argc, char *argv[])
{
    std::string ip;
    std::string portString;

    std::cout << "[Client] Starting client app..." << std::endl;
    std::cout << "Enter server IP address: ";
    std::getline(std::cin, ip);

    std::cout << "Enter server port number: ";
    std::getline(std::cin, portString);

    try
    {
        int port = 0;
        port = std::stoi(portString);
        Client c(port, ip);
        c.start();
    } catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
