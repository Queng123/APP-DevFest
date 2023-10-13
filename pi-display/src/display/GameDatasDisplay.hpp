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
    constexpr Color NORMAL_COLOR = GREEN;
    constexpr Color DAMAGED_COLOR = ORANGE;
    constexpr Color DESTROY_COLOR = RED;
    class GameDatasDisplay : public Display::IDisplay
    {
    public:
        enum class SHIP_ELEMENT
        {
            MIDDLE_PART = 1,
            WINDOW = 2,
            CABLE_MANAGEMENT = 3,
            CABLE_MANAGEMENT_OBJECT = 4,
            BOT_LEFT_WING = 5,
            BOT_LEFT_WING_DETAILS = 6,
            TOP_RIGHT_WING = 7,
            TOP_RIGHT_WING_DETAILS = 8,
            BOT_RIGHT_WING = 9,
            BOT_RIGHT_WING_DETAILS = 10,
            TOP_LEFT_WING = 11,
            TOP_LEFT_WING_DETAILS = 12
        };

    public:
        GameDatasDisplay(const Game::GameDatas &gameDatas)
            : _gameDatas(gameDatas), _windowIsOpen(true){};

        ~GameDatasDisplay(void){};

        void run(void) override;

        bool windowIsOpen(void) const { return _windowIsOpen; }

    private:
        void _updateShipStateScreen(void);
        void _updateRadarScreen(void);
        void _setupWindow(void);
        void _setupShaders(void);
        void _draw(void);
        void _update(void);
        void _updateShaders(void);
        void _handleEvent(void);
        void _drawRadar(void);
        void _drawBlasterOverheat(void);
        void _drawMissileWarning(void);
        void _drawShipState(void);
        void _drawWallsWarning(void);

    private:
        Color _getColorByStatus(Game::ShipState);
        const Game::GameDatas &_gameDatas;
        bool _windowIsOpen;
        const short _MAX_BLASTER_OVER_HEAT = 100;
        const float _RADAR_ANGLE = 0.78539816339;
        Shader _shaderCRT;
        Shader _shaderOverheat;
        Texture2D _textureCRT;
        Model _xWingModel;
        RenderTexture2D _radarRenderTexture;
        RenderTexture2D _radarRenderTexturePostProcess;
        RenderTexture2D _shipStateRenderTexture;
        RenderTexture2D _shipStateRenderTexturePostProcess;
    };
}
