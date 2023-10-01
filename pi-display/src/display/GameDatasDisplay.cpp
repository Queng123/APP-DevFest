/*
** EPITECH PROJECT, 2023
** APP-DevFest
** File description:
** GameDatasDisplay
*/

#include "GameDatasDisplay.hpp"

void Display::GameDatasDisplay::run(void)
{
    _setupWindow();
    _setupShaders();
    while (windowIsOpen())
    {
        _update();
    }
}
