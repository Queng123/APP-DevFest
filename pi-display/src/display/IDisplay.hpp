/*
** EPITECH PROJECT, 2023
** pi-display [WSL: Ubuntu]
** File description:
** IDisplay
*/

#pragma once

namespace Display
{
    class IDisplay
    {
    public:
        virtual ~IDisplay() = default;

        virtual void run() = 0;
    };
}
