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

typedef struct {
    char a[255];
} HuiInfo;

int main(void)
{
    Network::ThreadedUDPClient<Game::GameDatas, HuiInfo> client;
    Display::ThreadedGameDatasDisplay display(*client);

    while (display.windowIsOpen()) {
        // std::cout << client->shipPos.x << std::endl;
    }
}
