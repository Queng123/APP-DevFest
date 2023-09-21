/*
** EPITECH PROJECT, 2023
** pi-display [WSL: Ubuntu]
** File description:
** IClient
*/

#pragma once

#include "Network.hpp"

namespace Network {
    template<typename Receive, typename Send>
    class IClient {
        public:
            virtual ~IClient() = default;

            /**
             * @brief Connect to the server
             * @param ip The ip of the server
             * @param port The port of the server
             * @note This function is called in the constructor
            */
            virtual void connect(const std::string &ip, unsigned short port) = 0;
            /**
             * @brief Disconnect from the server
             * @note This function is called in the destructor
            */
            virtual void disconnect() = 0;
            /**
             * @brief Execute all the actions needed to send and receive messages
            */
            virtual int update() = 0;
            /**
             * @brief Execute loop until stop is called
            */
            virtual void run() = 0;
            
    };
}
