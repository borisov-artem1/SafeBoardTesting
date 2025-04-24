#pragma once
#include <cstdint>


class DisplayServer {
    int port;
public:
    explicit DisplayServer(const uint16_t port) : port(port) {};
    [[noreturn]] void start();
};
