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

int main(int ac, char *av[])
{
    if (ac != 3) {
        std::cerr << "Usage: " << av[0] << " <ip> <port>" << std::endl;
        return 84;
    }
    Network::ThreadedUDPClient<Game::GameDatas, Game::IOInfos> client(av[1], std::atoi(av[2]));
    Display::ThreadedGameDatasDisplay display(*client);
    IO::ThreadedIOHandler ioHandler;

    while (display.windowIsOpen()) {
        client = *ioHandler;
        ioHandler = *client;
    }
}
