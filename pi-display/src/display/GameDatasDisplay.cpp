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

void Display::GameDatasDisplay::_setupWindow(void)
{
    InitWindow(800, 600, "GameDatasDisplay");
    SetTargetFPS(60);
    ToggleFullscreen();
}

void Display::GameDatasDisplay::_setupShaders(void)
{
    _shaderCRT = LoadShader(0, "assets/shaders/CRT.fs");
    _textureCRT = LoadTexture("assets/textures/CRT.png");
    _radarImage = GenImageColor(10, 10, RED);
    _radar = LoadTextureFromImage(_radarImage);
    _shipStateImage = GenImageColor(10, 10, RED);
    _shipState = LoadTextureFromImage(_shipStateImage);
}

#include <iostream>
void Display::GameDatasDisplay::_draw(void)
{
    BeginDrawing();
    BeginShaderMode(_shaderCRT);
    ClearBackground(BLACK);

    DrawTexture(_shipState, 0, 0, WHITE);
    DrawTexture(_radar, GetRenderWidth() / 2, 0, WHITE);

    // DrawTexture(_textureCRT, 0, 0, WHITE); //* DEBUG
    // DrawTexture(_textureCRT, 500, 500, WHITE); //* DEBUG
    EndShaderMode();
    EndDrawing();
}

void Display::GameDatasDisplay::_updateShipStateScreen(void)
{
    if (_shipStateImage.width != GetRenderWidth() / 2 || _shipStateImage.height != GetRenderHeight()) {
        UnloadImage(_shipStateImage);
        _shipStateImage = GenImageColor(GetRenderWidth() / 2, GetRenderHeight(), BLACK);
    }
    ImageClearBackground(&_shipStateImage, {0, 11, 3, 255});

    // Apply ship state

    if (_shipState.width != _shipStateImage.width || _shipState.height != _shipStateImage.height) {
        UnloadTexture(_shipState);
        _shipState = LoadTextureFromImage(_shipStateImage);
    } else {
        UpdateTexture(_shipState, _shipStateImage.data);
    }
}

void Display::GameDatasDisplay::_updateRadarScreen(void)
{
    if (_radarImage.width != GetRenderWidth() / 2 || _radarImage.height != GetRenderHeight()) {
        UnloadImage(_radarImage);
        _radarImage = GenImageColor(GetRenderWidth() / 2, GetRenderHeight(), BLACK);
    }
    ImageClearBackground(&_radarImage, {0, 11, 3, 255});

    // Apply radar

    if (_radar.width != _radarImage.width || _radar.height != _radarImage.height) {
        UnloadTexture(_radar);
        _radar = LoadTextureFromImage(_radarImage);
    } else {
        UpdateTexture(_radar, _radarImage.data);
    }
}

void Display::GameDatasDisplay::_updateShaders(void)
{
    static float seconds = 0;
    seconds += GetFrameTime();
    float screenSize[2] = {(float)GetScreenWidth(), (float)GetScreenHeight()};

    SetShaderValue(_shaderCRT, GetShaderLocation(_shaderCRT, "iResolution"), &screenSize, SHADER_UNIFORM_VEC2);
    SetShaderValue(_shaderCRT, GetShaderLocation(_shaderCRT, "iTime"), &seconds, SHADER_UNIFORM_FLOAT);
}

void Display::GameDatasDisplay::_update(void)
{
    _updateShaders();
    _updateShipStateScreen();
    _updateRadarScreen();
    _draw();
    _handleEvent();
}

void Display::GameDatasDisplay::_handleEvent(void)
{
    if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
    {
        CloseWindow();
        _windowIsOpen = false;
    }
}

void Display::GameDatasDisplay::_drawRadar(void)
{
    DrawText(("X: " + std::to_string(_gameDatas.shipPos.x)).c_str(), 60, 0, 20, RED);
    DrawText(("Y: " + std::to_string(_gameDatas.shipPos.y)).c_str(), 60, 20, 20, RED);
}

void Display::GameDatasDisplay::_drawBlasterOverheat(void)
{
    DrawText(std::to_string(_gameDatas.blasterOverheat).c_str(), 0, 0, 20, RED);
}

void Display::GameDatasDisplay::_drawMissileWarning(void)
{
    DrawText(std::to_string(_gameDatas.missileWarning).c_str(), 40, 0, 20, RED);
}

void Display::GameDatasDisplay::_drawShipState(void)
{
    for (int i = 0; i < 5; i++)
    {
        DrawText(std::to_string(_gameDatas.shipState[i]).c_str(), 0, 20 + (i * 20), 20, RED);
    }
}

void Display::GameDatasDisplay::_drawWallsWarning(void)
{
    DrawText(std::to_string(_gameDatas.wallsWarning).c_str(), 40, 20, 20, RED);
}
