#include "ProcessingServer.h"

#include <limits>
#include <sstream>
#include <unordered_set>
#include <utility>

#include "../socket/Socket.h"


ProcessingServer::ProcessingServer(std::string ip,
                                   const uint16_t listenPort,
                                   const uint16_t displayPort)
    : ip(std::move(ip)), listenPort(listenPort), displayPort(displayPort) {}



void ProcessingServer::start()
{
    Socket clientListener(AF_INET, SOCK_STREAM, 0);

    if (!clientListener.BindAndListen(listenPort))
    {
        throw std::runtime_error("Failed to bind listener");
    }

    std::cout << "[Processing server] Listening on port " << listenPort << std::endl;

    Socket displayConnection(AF_INET, SOCK_STREAM, 0);
    if (!displayConnection.ConnectTo(ip, displayPort))
    {
        throw std::runtime_error("Failed to connect to server");
    }
    std::cout << "[Processing server] Connected to display server" << std::endl;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(displayPort);
    socklen_t addrLen = sizeof(addr);

    while (true)
    {
        Socket client(clientListener.Accept(reinterpret_cast<sockaddr*>(&addr), addrLen));

        while (true)
        {
            std::string input = client.ReceiveString();
            if (input.empty())
            {
                std::cerr << "[Processing server] Empty input" << std::endl;
                continue;
            }

            std::cout << "[Processing server] Received input: " << input << std::endl;
            client.SendString("Message from client received correctly");
            std::cout << "[Processing server] Sending message" << std::endl;

            std::string processed = removeDuplicates(input);

            displayConnection.SendString(processed);
        }

    }

}

std::string ProcessingServer::removeDuplicates(const std::string& input)
{
    std::string result;
    std::istringstream strStream(input);
    std::unordered_set<std::string> set;

    std::string word;
    while (strStream >> word)
    {
        if (set.insert(word).second)
        {
            result += word + " ";
        }
    }

    if (!result.empty() && result.back() == ' ')
    {
        result.pop_back();
    }
    return result;

}

uint16_t ProcessingServer::stringToUint16Conversion(const std::string& stringPort)
{
    const unsigned long value = std::stoul(stringPort);

    if (value > std::numeric_limits<uint16_t>::max())
    {
        throw std::out_of_range("Value is out of range");
    }
    return static_cast<uint16_t>(value);
}

