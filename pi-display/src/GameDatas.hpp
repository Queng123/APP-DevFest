/*
** EPITECH PROJECT, 2023
** pi-display [WSL: Ubuntu]
** File description:
** GameDatas
*/

#pragma once

#include <cstdint>

#include "Vectors.hpp"

#define MAGIC_NUMBER 0xf04a4e

namespace Game
{
    enum ShipState
    {
        SHIP_STATE_NORMAL = 3,
        SHIP_STATE_SLIGHTLY_DAMAGED = 2,
        SHIP_STATE_DAMAGED = 1,
    };
    struct GameDatas
    {
        Vectors::Vector2f shipPos;
        uint8_t nbEnemies;
        Vectors::Vector2f enemiesPos[8];
        uint8_t nbMissiles;
        Vectors::Vector2f missilesPos[8];
        short blasterOverheat;
        uint8_t shipState[5];
        bool missileWarning;
        bool wallsWarning;
        bool canSendBomb;
        unsigned int magicNumber;
    };

    struct IOInfos
    {
        bool shipStarted;
        bool bombLaunched;
        unsigned int magicNumber;
    };
}
