/*
** EPITECH PROJECT, 2023
** pi-display [WSL: Ubuntu]
** File description:
** GameDatasDisplay
*/

#pragma once

#include <raylib.h>
#include <cmath>

#include "IDisplay.hpp"
#include "GameDatas.hpp"

namespace Display {
    class GameDatasDisplay : public Display::IDisplay {
        public:
            GameDatasDisplay(const Game::GameDatas &gameDatas)
                : _gameDatas(gameDatas), _windowIsOpen(true)
            {

            }
            ~GameDatasDisplay()
            {

            }

            void run() override
            {
                _setupWindow();
                while (_windowIsOpen) {
                    _update();
                }
                CloseWindow();
            }
            bool windowIsOpen() const
            {
                return _windowIsOpen;
            }
        private:
            void _setupWindow()
            {
                InitWindow(800, 600, "GameDatasDisplay");
                SetTargetFPS(60);
                ToggleFullscreen();
            }
            void _draw()
            {
                BeginDrawing();
                ClearBackground(BLACK);
                _drawRadar();
                _drawBlasterOverheat();
                _drawMissileWarning();
                _drawShipState();
                _drawWallsWarning();
                EndDrawing();
            }
            void _update()
            {
                _draw();
                _handleEvent();
            }
            void _handleEvent()
            {
                if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
                    _windowIsOpen = false;
            }
            void _drawRadar()
            {
                // draw a cone representing the radar
                DrawTriangle(
                    {400, 300},
                    {(float)(400 + (cos(_RADAR_ANGLE) * 200)), (float)(300 + (sin(_RADAR_ANGLE) * 200))},
                    {(float)(400 + (cos(-_RADAR_ANGLE) * 200)), (float)(300 + (sin(-_RADAR_ANGLE) * 200))},
                    RED
                );
            }
            void _drawBlasterOverheat()
            {
                DrawRectangle(0, 0, _gameDatas.blasterOverheat, 20, RED);
                DrawRectangle(0, 0, _MAX_BLASTER_OVER_HEAT, 20, GREEN);
            }
            void _drawMissileWarning()
            {
                DrawText(std::to_string(_gameDatas.missileWarning).c_str(), 40, 0, 20, RED);
            }
            void _drawShipState()
            {
                for (int i = 0; i < 5; i++) {
                    DrawText(std::to_string(_gameDatas.shipState[i]).c_str(), 0, 20 + (i * 20), 20, RED);
                }
            }
            void _drawWallsWarning()
            {
                DrawText(std::to_string(_gameDatas.wallsWarning).c_str(), 40, 20, 20, RED);
            }
        private:
            const Game::GameDatas &_gameDatas;
            bool _windowIsOpen;
            const short _MAX_BLASTER_OVER_HEAT = 100;
            const float _RADAR_ANGLE = 0.78539816339;
    };
}
