#include "Socket.h"

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <netinet/in.h>

bool Socket::isValidDomain(const int domain) const
{
    return domain == AF_INET || domain == AF_INET6 || domain == AF_UNIX;
}

bool Socket::isValidType(const int type) const
{
    return type == SOCK_STREAM || type == SOCK_DGRAM || type == SOCK_RAW;
}

bool Socket::isValidProtocol(const int protocol) const
{
    return protocol == 0 || protocol == IPPROTO_TCP || protocol == IPPROTO_UDP;
}


Socket::Socket(const int domain, const int type, const int protocol) : domain(domain), type(type), protocol(protocol)
{
    if (!isValidDomain(domain) && !isValidType(type) && !isValidProtocol(protocol))
    {
        throw std::invalid_argument("Invalid domain or type or protocol");
    }
    sock = socket(domain, type, protocol);
    if (sock < 0)
    {
        throw std::runtime_error("Failed to create socket");
    }
}

Socket& Socket::operator=(Socket&& other) noexcept
{
    if (this != &other)
    {
        if (sock >= 0) { close(sock); }
        sock = other.sock;
        other.sock = -1;
    }
    return *this;

}

Socket::~Socket()
{
    if (sock >= 0) { close(sock); }
}

Socket::Socket(Socket&& other) noexcept : sock(other.sock) { other.sock = -1; }

Socket::Socket(const int fd) : sock(fd) {}

int Socket::getSocketDescriptor() const { return sock; }

bool Socket::Bind(const int sock_fd, const sockaddr* addr, const socklen_t addr_len)
{
    if (const int result = bind(sock_fd, addr, addr_len); result < 0)
    {
        std::cerr << "Failed to bind socket " << sock_fd << std::endl;
        return false;
    }
    return true;
}

int Socket::getDomain() const
{
    return domain;
}

int Socket::getType() const
{
    return type;
}

int Socket::getProtocol() const
{
    return protocol;
}

bool Socket::Listen(const int backlog) const
{
    if (const int result = listen(sock, backlog); result < 0)
    {
        return false;
    }
    return true;
}

int Socket::Accept(sockaddr* addr, socklen_t& addr_len) const
{
    const int result = accept(sock, addr, &addr_len);
    if (result < 0)
    {
        throw std::runtime_error("Failed to accept connection");
    }
    return result;
}

bool Socket::ConnectTo(const std::string& host, const uint16_t port) const
{
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    constexpr int retires = 200;
    if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) <= 0)
    {
        return false;
    }

    for (int i = 0; i < retires; ++i)
    {
        constexpr int timeout = 1000;
        if (connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == 0)
        {
            return true;
        }

        std::cerr << "[Socket] Attempt " << i << " failed to connect to " << host << ":" << port
                  << ": " << strerror(errno) << "\n";


        std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
    }
    return connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) >= 0;
}

std::string Socket::ReceiveString() const
{
    uint32_t len;
    if (recv(sock, &len, sizeof(len), 0) != sizeof(len))
    {
        throw std::runtime_error("Failed to receive length from socket");
    }
    len = ntohl(len);
    std::string buffer(len, 0);
    const ssize_t result = recv(sock, buffer.data(), len, 0);
    if (result <= 0)
    {
        throw std::runtime_error("Failed to receive data from socket");
    }
    buffer.resize(result);
    return buffer;

}

bool Socket::SendString(const std::string& msg) const
{
    const uint32_t len = htonl(static_cast<uint32_t>(msg.size()));
    if (send(sock, &len, sizeof(len), 0) != sizeof(len))
    {
        throw std::runtime_error("Failed to send message");
    }
    return send(sock, msg.c_str(), msg.size(), 0) == static_cast<ssize_t>(msg.size());
}

bool Socket::BindAndListen(const uint16_t port)
{
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    if (!Bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)))
    {
        return false;
    }
    return Listen(5);
}

void Socket::Close() const
{
    close(sock);
}
