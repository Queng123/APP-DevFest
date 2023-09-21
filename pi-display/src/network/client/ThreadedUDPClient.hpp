/*
** EPITECH PROJECT, 2023
** pi-display [WSL: Ubuntu]
** File description:
** ThreadedUDPClient
*/

#pragma once

#include "UDPClient.hpp"

#include <thread>

namespace Network {
template<typename Receive, typename Send>
    class ThreadedUDPClient : public Network::UDPClient<Receive, Send>
    {
        public:
            ThreadedUDPClient()
                : Network::UDPClient<Receive, Send>()
            {
                _thread = std::thread(&ThreadedUDPClient::run, this);
            }
            ThreadedUDPClient(const std::string &ip, unsigned short port)
                : Network::UDPClient<Receive, Send>(ip, port)
            {
                _thread = std::thread(&ThreadedUDPClient::run, this);
            }

            ~ThreadedUDPClient()
            {
                pthread_kill(_thread.native_handle(), SIGUSR1);
                _thread.join();
            }
            void operator=(const Send &data)
            {
                Network::UDPClient<Receive, Send>::operator=(data);
            }
        private:
            std::thread _thread;
    };
}
