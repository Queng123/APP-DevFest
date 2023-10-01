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
            : _gameDatas(gameDatas), _windowIsOpen(true) {};

        ~GameDatasDisplay() {};

        void run(void) override;

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
        void _setupShaders()
        {
            _shaderCRT = LoadShader(0, "assets/shaders/CRT.fs");
            _textureCRT = LoadTexture("assets/textures/CRT.png");

        }
        void _draw()
        {
            static float seconds = 0;
            seconds += GetFrameTime();

            BeginDrawing();
            float screenSize[2] = {(float)GetScreenWidth(), (float)GetScreenHeight()};

            SetShaderValue(_shaderCRT, GetShaderLocation(_shaderCRT, "iResolution"), &screenSize, SHADER_UNIFORM_VEC2);

            SetShaderValue(_shaderCRT, GetShaderLocation(_shaderCRT, "iTime"), &seconds, SHADER_UNIFORM_FLOAT);

            BeginShaderMode(_shaderCRT);
            ClearBackground(BLACK);
            DrawTexture(_textureCRT, 0 ,0 , WHITE);
            DrawTexture(_textureCRT, 500, 500, WHITE);
            EndShaderMode();
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
            {
                CloseWindow();
                _windowIsOpen = false;
            }
        }
        void _drawRadar()
        {
            // draw a cone representing the radar
            // DrawTriangle(
            //     {400, 300},
            //     {(float)(400 + (cos(_RADAR_ANGLE) * 200)), (float)(300 + (sin(_RADAR_ANGLE) * 200))},
            //     {(float)(400 + (cos(-_RADAR_ANGLE) * 200)), (float)(300 + (sin(-_RADAR_ANGLE) * 200))},
            //     RED
            // );
            DrawText(("X: " + std::to_string(_gameDatas.shipPos.x)).c_str(), 60, 0, 20, RED);
            DrawText(("Y: " + std::to_string(_gameDatas.shipPos.y)).c_str(), 60, 20, 20, RED);
        }
        void _drawBlasterOverheat()
        {
            // DrawRectangle(0, 0, _gameDatas.blasterOverheat, 20, RED);
            // DrawRectangle(0, 0, _MAX_BLASTER_OVER_HEAT, 20, GREEN);
            DrawText(std::to_string(_gameDatas.blasterOverheat).c_str(), 0, 0, 20, RED);
        }
        void _drawMissileWarning()
        {
            DrawText(std::to_string(_gameDatas.missileWarning).c_str(), 40, 0, 20, RED);
        }
        void _drawShipState()
        {
            for (int i = 0; i < 5; i++)
            {
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
        Shader _shaderCRT;
        Texture2D _textureCRT;
    };
}
