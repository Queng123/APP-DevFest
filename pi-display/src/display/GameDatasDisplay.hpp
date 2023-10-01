/*
** EPITECH PROJECT, 2023
** pi-display [WSL: Ubuntu]
** File description:
** GameDatasDisplay
*/

#pragma once

#include <raylib.h>
#include <cmath>
#include <string>

#include "IDisplay.hpp"
#include "GameDatas.hpp"

namespace Display
{
    class GameDatasDisplay : public Display::IDisplay
    {
    public:
        GameDatasDisplay(const Game::GameDatas &gameDatas)
            : _gameDatas(gameDatas), _windowIsOpen(true){};

        ~GameDatasDisplay(void){};

        void run(void) override;

        bool windowIsOpen(void) const { return _windowIsOpen; }

    private:
        void _setupWindow(void);
        void _setupShaders(void);
        void _draw(void);
        void _update(void);
        void _handleEvent(void);
        void _drawRadar(void);
        void _drawBlasterOverheat(void);
        void _drawMissileWarning(void);
        void _drawShipState(void);
        void _drawWallsWarning(void);

    private:
        const Game::GameDatas &_gameDatas;
        bool _windowIsOpen;
        const short _MAX_BLASTER_OVER_HEAT = 100;
        const float _RADAR_ANGLE = 0.78539816339;
        Shader _shaderCRT;
        Texture2D _textureCRT;
    };
}
