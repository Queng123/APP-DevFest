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
    _radarRenderTexture = LoadRenderTexture(GetRenderWidth() / 2, GetRenderHeight());
    _shipStateRenderTexture = LoadRenderTexture(GetRenderWidth() / 2, GetRenderHeight());
}

#include <iostream>
void Display::GameDatasDisplay::_draw(void)
{
    BeginDrawing();
    BeginShaderMode(_shaderCRT);
    ClearBackground(BLACK);

    DrawTexture(_shipStateRenderTexture.texture, 0, 0, WHITE);
    DrawTexture(_radarRenderTexture.texture, GetRenderWidth() / 2, 0, WHITE);

    // DrawTexture(_textureCRT, 0, 0, WHITE); //* DEBUG
    // DrawTexture(_textureCRT, 500, 500, WHITE); //* DEBUG
    EndShaderMode();
    EndDrawing();
}

void Display::GameDatasDisplay::_updateShipStateScreen(void)
{
    if (_shipStateRenderTexture.texture.width != GetRenderWidth() / 2 || _shipStateRenderTexture.texture.height != GetRenderHeight()) {
        UnloadRenderTexture(_shipStateRenderTexture);
        _shipStateRenderTexture = LoadRenderTexture(GetRenderWidth() / 2, GetRenderHeight());
    }
    BeginTextureMode(_shipStateRenderTexture);
    ClearBackground(BLACK);
    static Camera camera = { (Vector3){ 0.0f, 10.0f, 10.0f }, (Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE };
    BeginMode3D(camera);
    DrawCube(Vector3{0, 0, 0}, 2, 2, 2, RED);
    EndMode3D();
    // _drawBlasterOverheat();
    // _drawMissileWarning();
    // _drawShipState();
    EndTextureMode();
}

void Display::GameDatasDisplay::_updateRadarScreen(void)
{
    if (_radarRenderTexture.texture.width != GetRenderWidth() / 2 || _radarRenderTexture.texture.height != GetRenderHeight()) {
        UnloadRenderTexture(_radarRenderTexture);
        _radarRenderTexture = LoadRenderTexture(GetRenderWidth() / 2, GetRenderHeight());
    }
    BeginTextureMode(_radarRenderTexture);
    ClearBackground(BLACK);
    // _drawRadar();
    // _drawWallsWarning();
    EndTextureMode();
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
