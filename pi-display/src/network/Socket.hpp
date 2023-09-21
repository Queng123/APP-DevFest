/*
** EPITECH PROJECT, 2023
** pi-display [WSL: Ubuntu]
** File description:
** Socket
*/

#pragma once

#include <Network.hpp>

namespace Network
{
    class Socket
    {
    public:
        Socket(const std::string &ip, int port)
        {
        }

    private:
        int _fd;
        std::string _ip;
    };
    bool GetSockName(std::string &address, int &port)
    {
        if (socket_ == 0)
        {
            std::cerr << "Socket is not open" << std::endl;
            return false;
        }
        struct sockaddr_in socketAddress
        {
        };
        socklen_t addressLength = sizeof(socketAddress);
        int result = getsockname(socket_, (struct sockaddr *)&socketAddress, &addressLength);
        if (result < 0)
        {
            std::cerr << "Failed to get socket name" << std::endl;
            return false;
        }
        char ipBuffer[INET_ADDRSTRLEN];
        const char *ipAddress = inet_ntop(Protocol::Domain, &(socketAddress.sin_addr), ipBuffer, sizeof(ipBuffer));
        if (ipAddress == nullptr)
        {
            std::cerr << "Failed to convert IP address" << std::endl;
            return false;
        }
        address = ipAddress;
        port = ntohs(socketAddress.sin_port);
        return true;
    }

private:
    int socket_;
};
}
