#pragma once
#include <memory>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


class Socket {
    int domain{AF_INET};
    int type{SOCK_STREAM};
    int protocol{0};
    int sock;
    friend class Utils;
public:
    explicit Socket(int domain, int type, int protocol);
    explicit Socket(int fd);
    ~Socket();

    Socket(const Socket& other) = delete;
    Socket& operator=(const Socket& other) = delete;
    Socket(Socket&& other) noexcept;
    Socket& operator=(Socket&& other) noexcept;

    bool Bind(int sock_fd, const sockaddr* addr, socklen_t addr_len);
    bool Listen(int backlog) const;
    [[nodiscard]] int Accept(sockaddr* addr, socklen_t& addr_len) const;
    bool ConnectTo(const std::string& host, uint16_t port) const;
    bool BindAndListen(uint16_t port);
    bool SendString(const std::string& msg) const;
    [[nodiscard]] std::string ReceiveString() const;
    bool isValidDomain(int domain) const;
    bool isValidType(int type) const;
    bool isValidProtocol(int protocol) const;
    [[nodiscard]] int getSocketDescriptor() const;
    [[nodiscard]] int getDomain() const;
    [[nodiscard]] int getType() const;
    [[nodiscard]] int getProtocol() const;
    void Close() const;

};
