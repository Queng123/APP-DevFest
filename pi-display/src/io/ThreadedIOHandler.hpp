/*
** EPITECH PROJECT, 2023
** APP-DevFest [WSL: Ubuntu]
** File description:
** ThreadedIOHandler
*/

#pragma once

#include "IOHandler.hpp"

#include <thread>

namespace IO {
    class ThreadedIOHandler : public IOHandler {
        public:
            ThreadedIOHandler()
                : IOHandler()
            {
                _thread = std::thread(&ThreadedIOHandler::run, this);
            }
            ~ThreadedIOHandler()
            {
                stop();
                _thread.join();
            }

            void run()
            {
                while (!getNeedsToStop()) {
                    update();
                }
            }
            void operator=(const Game::GameDatas &data)
            {
                IOHandler::operator=(data);
            }
        private:
            std::thread _thread;
    };
}
