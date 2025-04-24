#pragma once
#include <iostream>
#include <utility>

class Client {
    std::string ip;
    int port;
public:
    explicit Client(const int port, std::string  ip) : ip(std::move(ip)), port(port) {}
    void start();
};

