#include "ProcessingServer.h"




int main()
{
    std::string ip;
    std::string listenPort;
    std::string displayPort;

    std::cout << "[Processing server] Starting processing server..." << std::endl;
    std::cout << "Enter server IP address: ";
    std::getline(std::cin, ip);

    std::cout << "Enter listen port number: ";
    std::getline(std::cin, listenPort);

    std::cout << "Enter display port number: ";
    std::getline(std::cin, displayPort);

    try
    {
        const uint16_t listen = ProcessingServer::stringToUint16Conversion(listenPort);
        const uint16_t display = ProcessingServer::stringToUint16Conversion(displayPort);
        ProcessingServer ps(ip, listen, display);
        ps.start();
    } catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}