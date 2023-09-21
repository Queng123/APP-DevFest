/*
** EPITECH PROJECT, 2023
** pi-display [WSL: Ubuntu]
** File description:
** ThreadedGameDatasDisplay
*/

#pragma once

#include "GameDatasDisplay.hpp"

#include <thread>

namespace Display
{
    class ThreadedGameDatasDisplay : public GameDatasDisplay {
    public:
        ThreadedGameDatasDisplay(const Game::GameDatas &gameDatas)
            : GameDatasDisplay(gameDatas)
        {
            _thread = std::thread(&ThreadedGameDatasDisplay::run, this);
        }
        ~ThreadedGameDatasDisplay()
        {
            _thread.join();
        }
    private:
        std::thread _thread;
    };
}
