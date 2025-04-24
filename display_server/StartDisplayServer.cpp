#include <iostream>

#include "DisplayServer.h"
#include "../processing_server/ProcessingServer.h"

int main()
{
    std::string portString;

    std::cout << "[Client] Starting display server..." << std::endl;

    std::cout << "Enter server port number: ";
    std::getline(std::cin, portString);

    try
    {
        const uint16_t port = ProcessingServer::stringToUint16Conversion(portString);
        DisplayServer ds(port);
        ds.start();
    } catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

}