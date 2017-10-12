//
// Created by Good_Pudge.
//

#include "../../util/util.hpp"
#include "../../include/Exception.hpp"
#include "../../include/Socket.hpp"
#include "../../include/InetAddress.hpp"
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>

namespace ohf {
    Socket::Socket() :
            ios(std::make_shared<std::iostream>(new StreamBuf(this))) {
        if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            throw Exception(Exception::Code::FAILED_TO_CREATE_SOCKET, "Failed to create socket: " +
                                                                      std::string(strerror(errno)));
    }

    Socket::~Socket() {
        close(socket_fd);
    }

    std::iostream &Socket::connect(const std::string &address, const int &port) const {
        // Address setup
        sockaddr_in addr;
        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;// TCP/IP
        addr.sin_addr.s_addr = inet_addr(InetAddress(address).hostAddress().c_str());
        addr.sin_port = htons(port); // Port
        // Connect
        if (::connect(socket_fd, (sockaddr * ) & addr, sizeof(addr)) < 0)
            throw Exception(Exception::Code::FAILED_TO_CREATE_CONNECTION, "Failed to create connection: " +
                                                                          std::string(strerror(errno)));

        return *ios;
    }

    void Socket::send(const char *data, int size) const {
        if (write(socket_fd, data, size) < 0)
            throw Exception(Exception::Code::FAILED_TO_SEND_DATA,
                            "Failed to send data: " + std::string(strerror(errno)));
    }

    std::vector<char> Socket::receive(size_t size) const {
        int len = 0;
        std::vector<char> buffer(size);
        if ((len = read(socket_fd, &buffer.at(0), size)) < 0)
            throw Exception(Exception::Code::FAILED_TO_RECEIVE_DATA, "Failed to receive data: " +
                                                                     std::string(strerror(errno)));
        return std::vector<char>(buffer.begin(), buffer.begin() + len);
    }

    void Socket::shutdown(int how) const {
        if (::shutdown(socket_fd, how) < 0)
            throw Exception(Exception::Code::FAILED_TO_SHUTDOWN_SOCKET, "Failed to disconnect: " +
                                                                        std::string(strerror(errno)));
    }
}