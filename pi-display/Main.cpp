/*
** EPITECH PROJECT, 2023
** pi-display [WSL: Ubuntu]
** File description:
** Main
*/

#include <iostream>
#include "ThreadedUDPClient.hpp"
#include "GameDatas.hpp"
#include "ThreadedGameDatasDisplay.hpp"
#include "ThreadedIOHandler.hpp"

int main(void)
{
    Network::ThreadedUDPClient<Game::GameDatas, Game::IOInfos> client;
    Display::ThreadedGameDatasDisplay display(*client);
    IO::ThreadedIOHandler ioHandler;

    while (display.windowIsOpen()) {
        client = *ioHandler;
        ioHandler = *client;
    }
}
