#pragma once
#include <iostream>
#include <cstdint>

class ProcessingServer {
    std::string ip;
    uint16_t listenPort;
    uint16_t displayPort;
public:
    explicit ProcessingServer(std::string ip, uint16_t listenPort, uint16_t displayPort);
    static std::string removeDuplicates(const std::string& input);
    static uint16_t stringToUint16Conversion(const std::string& stringPort);
    void start();
};
