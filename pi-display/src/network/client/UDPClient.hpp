/*
** EPITECH PROJECT, 2023
** pi-display [WSL: Ubuntu]
** File description:
** UDPClient
*/

#pragma once

#include "IClient.hpp"

#include <csignal>

namespace Network
{
    template <typename Receive, typename Send>
    class UDPClient : public Network::IClient<Receive, Send>
    {
    public:
        UDPClient(const std::string &ip = "127.0.0.1", unsigned short port = 12345)
            : _fd(-1), _servinfo(nullptr)
        {
            memset(&_sendData, 0, sizeof(Send));
            memset(&_receiveData, 0, sizeof(Receive));
            std::signal(SIGUSR1, &UDPClient::_sigHandler);
            connect(ip, port);
        }
        ~UDPClient()
        {
            disconnect();
        }

        void disconnect() override
        {
            if (_fd != -1)
            {
                Network::close(_fd);
            }
            if (_servinfo != nullptr)
            {
                Network::freeaddrinfo(_servinfo);
                _servinfo = nullptr;
            }
        }
        int update() override
        {
            int ret = 0;
            fd_set readfds;
            timeval tv = {0, 500};

            FD_ZERO(&readfds);
            FD_SET(_fd, &readfds);
            try {
                ret = Network::select(_fd + 1, &readfds, nullptr, nullptr, &tv);
                if (FD_ISSET(_fd, &readfds))
                {
                    _receive();
                }
                _send();
            } catch (const Network::PerrorException &e) {
                if (e != EINTR)
                {
                    throw e;
                } else {
                    ret = -1;
                }
            }
            return ret;
        }

        void run() override
        {
            while (update() >= 0);
        }
        const Receive *operator->() const
        {
            return &_receiveData;
        }
        const Receive &operator*() const
        {
            return _receiveData;
        }
        void operator=(const Send &message)
        {
            _sendData = message;
        }
        void connect(const std::string &ip, unsigned short port) override
        {
            struct addrinfo hints;

            if (_fd != -1)
            {
                disconnect();
            }
            memset(&hints, 0, sizeof(struct addrinfo));
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_DGRAM;
            try
            {
                Network::getaddrinfo(ip.c_str(), std::to_string(port).c_str(), &hints, &_servinfo);
                _fd = Network::socket(AF_INET, SOCK_DGRAM, 0);
                Network::sendto(_fd, "\0", 1, MSG_CONFIRM, _servinfo->ai_addr, _servinfo->ai_addrlen);
            }
            catch (const std::exception &e)
            {
                disconnect();
                throw e;
            }
        }
    private:
        static void _sigHandler(int sig)
        {
            (void)sig;
        }
        void _receive()
        {
            ssize_t received = Network::recvfrom(_fd, &_receiveData, sizeof(Receive), 0, _servinfo->ai_addr, &_servinfo->ai_addrlen);
            std::cerr << "Received " << received << " bytes" << std::endl;
        }
        void _send()
        {
            ssize_t sended = Network::sendto(_fd, &_sendData, sizeof(Send), 0, _servinfo->ai_addr, _servinfo->ai_addrlen);
        }

    private:
        int _fd;
        struct addrinfo *_servinfo;
        Receive _receiveData;
        Send _sendData;
    };
}
