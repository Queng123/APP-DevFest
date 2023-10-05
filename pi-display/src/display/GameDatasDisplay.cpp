/*
** EPITECH PROJECT, 2023
** APP-DevFest
** File description:
** GameDatasDisplay
*/

#include "GameDatasDisplay.hpp"
#include "raymath.h"
#include <iostream>
#include <vector>

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
    _xWingModel = LoadModel("assets/models/x-wing final.gltf");
    if (IsModelReady(_xWingModel)) {
        // 0 I don't know
        // 1 middle part
        // 2 Window
        // 3 Cable management behind
        // 4 object in cable management
        // 5 Bot Left Wing
        // 6 Details Bot Left (osef)
        // 7 Top Right Wing
        // 8 Details Top Right (osef)
        // 9 Bot Right Wing
        // 10 Details Bot Right (osef)
        // 11 Top Left Wing
        // 12 Details Top Left (osef)
        _xWingModel.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("assets/textures/cabina.png");
        _xWingModel.materials[2].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("assets/textures/cabina.png");
        _xWingModel.materials[2].maps[MATERIAL_MAP_DIFFUSE].color = (Color){0, 0, 0, 100};
        _xWingModel.materials[3].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("assets/textures/cabina.png");
        _xWingModel.materials[4].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("assets/textures/cabina.png");
        _xWingModel.materials[5].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("assets/textures/ala._2.png");
        _xWingModel.materials[6].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("assets/textures/detalles.png");
        _xWingModel.materials[7].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("assets/textures/ala._2.png");
        _xWingModel.materials[8].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("assets/textures/detalles.png");
        _xWingModel.materials[9].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("assets/textures/ala._2.png");
        _xWingModel.materials[10].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("assets/textures/detalles.png");
        _xWingModel.materials[11].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("assets/textures/ala._2.png");
        _xWingModel.materials[12].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("assets/textures/detalles.png");
        _xWingModel.transform = MatrixRotateX(PI / 2);
    }
}

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
    ClearBackground((Color){0, 10, 3, 0});

    static Camera camera = { (Vector3){ 20.0f, -10.0f, 0.0f }, (Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ 0.0f, 1.0f, 0.0f }, 10.0f, CAMERA_ORTHOGRAPHIC   };
    static float rotation = 0.0f;
    rotation += GetFrameTime() * 10;

    // BeginMode3D(camera);
    // if (IsModelReady(_xWingModel)) {
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::BOT_LEFT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = DAMAGED_COLOR;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::TOP_RIGHT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = DESTROY_COLOR;
    //     DrawModelEx(_xWingModel, (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 1.0f, 0.0f}, rotation, (Vector3){3.0f, 3.0f, 3.0f}, WHITE);
    // }
    // EndMode3D();

    // BeginMode3D(camera);
    // if (IsModelReady(_xWingModel)) {
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::BOT_LEFT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = DAMAGED_COLOR;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::TOP_RIGHT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = DESTROY_COLOR;
    //     DrawModelEx(_xWingModel, (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 1.0f, 0.0f}, rotation, (Vector3){3.0f, 3.0f, 3.0f}, {255, 255, 255, 100});
    //     DrawModelWiresEx(_xWingModel, (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 1.0f, 0.0f}, rotation, (Vector3){3.0f, 3.0f, 3.0f}, GREEN);
    // }
    // EndMode3D();

    // BeginMode3D(camera);
    // if (IsModelReady(_xWingModel)) {
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::BOT_LEFT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = DAMAGED_COLOR;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::TOP_RIGHT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = DESTROY_COLOR;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::BOT_RIGHT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::TOP_LEFT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::BOT_LEFT_WING_DETAILS)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::TOP_RIGHT_WING_DETAILS)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::BOT_RIGHT_WING_DETAILS)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::TOP_LEFT_WING_DETAILS)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::MIDDLE_PART)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::WINDOW)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::CABLE_MANAGEMENT)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::CABLE_MANAGEMENT_OBJECT)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     DrawModelWiresEx(_xWingModel, (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 1.0f, 0.0f}, rotation, (Vector3){3.0f, 3.0f, 3.0f}, WHITE);
    // }
    // EndMode3D();

    BeginMode3D(camera);
    if (IsModelReady(_xWingModel)) {
        _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::BOT_LEFT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = DAMAGED_COLOR;
        _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::TOP_RIGHT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = DESTROY_COLOR;
        _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::BOT_RIGHT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
        _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::TOP_LEFT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
        _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::BOT_LEFT_WING_DETAILS)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
        _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::TOP_RIGHT_WING_DETAILS)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
        _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::BOT_RIGHT_WING_DETAILS)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
        _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::TOP_LEFT_WING_DETAILS)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
        _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::MIDDLE_PART)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
        _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::WINDOW)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
        _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::CABLE_MANAGEMENT)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
        _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::CABLE_MANAGEMENT_OBJECT)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
        DrawModelWiresEx(_xWingModel, (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 1.0f, 0.0f}, rotation, (Vector3){3.0f, 3.0f, 3.0f}, WHITE);
        DrawModelEx(_xWingModel, (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 1.0f, 0.0f}, rotation, (Vector3){3.0f, 3.0f, 3.0f}, { 255, 255, 255, 100 });
    }
    EndMode3D();

    // BeginMode3D(camera);
    // if (IsModelReady(_xWingModel)) {
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::BOT_LEFT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = DAMAGED_COLOR;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::TOP_RIGHT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = DESTROY_COLOR;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::BOT_RIGHT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::TOP_LEFT_WING)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::BOT_LEFT_WING_DETAILS)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::TOP_RIGHT_WING_DETAILS)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::BOT_RIGHT_WING_DETAILS)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::TOP_LEFT_WING_DETAILS)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::MIDDLE_PART)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::WINDOW)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::CABLE_MANAGEMENT)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     _xWingModel.materials[static_cast<int>(SHIP_ELEMENT::CABLE_MANAGEMENT_OBJECT)].maps[MATERIAL_MAP_DIFFUSE].color = GREEN;
    //     DrawModelWiresEx(_xWingModel, (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 1.0f, 0.0f}, rotation, (Vector3){3.0f, 3.0f, 3.0f}, WHITE);
    //     DrawModelEx(_xWingModel, (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 1.0f, 0.0f}, rotation, (Vector3){3.0f, 3.0f, 3.0f}, { 0, 228, 48, 100 });
    // }
    // EndMode3D();

    EndTextureMode();
}

void Display::GameDatasDisplay::_updateRadarScreen(void)
{
    if (_radarRenderTexture.texture.width != GetRenderWidth() / 2 || _radarRenderTexture.texture.height != GetRenderHeight()) {
        UnloadRenderTexture(_radarRenderTexture);
        _radarRenderTexture = LoadRenderTexture(GetRenderWidth() / 2, GetRenderHeight());
    }
    BeginTextureMode(_radarRenderTexture);
    ClearBackground((Color){0, 10, 3, 255});
    _drawRadar();
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
    static float angle = 0.0f; // From 0 to 360
    const static float angleSpeed = 1.f;
    const static float distance = 20.f;
    static std::vector<std::pair<std::pair<float, float>, float>> detectedEnemies; // float is 10 and decrease by 0.1 each frame. It allow to display enemies on radar and remove them after a while
    std::vector<std::pair<float, float>> enemiesInCircle;
    Vector2 circleCenter = {GetRenderWidth() / 4.f, (float)GetRenderHeight() / 2.f};
    float radius = (float)GetRenderWidth() / 5.f;

    angle += angleSpeed;
    if (angle >= 360)
        angle -= 360;

    DrawCircleGradient(circleCenter.x, circleCenter.y, radius, (Color){0, 0, 0, 0}, (Color){0, 20, 7, 255});
    DrawCircleLines(circleCenter.x, circleCenter.y, radius, (Color){0, 50, 10, 255});
    DrawLine(circleCenter.x, circleCenter.y, circleCenter.x + radius * cosf(DEG2RAD * angle), circleCenter.y + radius * sinf(DEG2RAD * angle), (Color){0, 255, 0, 255});

    for (size_t i = 0; i < _gameDatas.nbEnemies; i++)
    {
        float ratio = radius / distance;
        Vector2 enemyPos = {(float)_gameDatas.enemiesPos[i].x - (float)_gameDatas.shipPos.x, (float)_gameDatas.enemiesPos[i].y - (float)_gameDatas.shipPos.y};
        if (Vector2Length(enemyPos) <= distance)
            enemiesInCircle.push_back({enemyPos.x * ratio, enemyPos.y * ratio});
    }

    for (auto &enemyInCircle: enemiesInCircle)
    {
        // check if enemy is in the angle of the circle
        // add it
        detectedEnemies.push_back(std::pair<std::pair<float, float>, float>(enemyInCircle, 1.f));
    }

    for (auto &detectedEnemy: detectedEnemies)
    {
        DrawCircle(detectedEnemy.first.first + circleCenter.x, detectedEnemy.first.second + circleCenter.y, 5, (Color){0, static_cast<unsigned char>(255.f * detectedEnemy.second), 0, 255});
        detectedEnemy.second -= 0.01;
        if (detectedEnemy.second <= 0)
            detectedEnemies.erase(detectedEnemies.begin());
    }
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
