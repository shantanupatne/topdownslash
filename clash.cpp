#include <iostream>
#ifndef RAYMATH
#define RAYMATH
#include "raylib.h"
#include "raymath.h"
#endif

#include "includes/character.h"
#include "includes/prop.h"
#include "includes/enemy.h"

Color Overlay = {0, 0, 0, 128};
const int win_offset{32};
int main()
{
    const int win_size{384};

    InitWindow(win_size, win_size + win_offset, "Classy Clash");
    Texture2D worldMap = LoadTexture("nature_tileset/WorldMap.png");

    Vector2 mapPos{};
    float mapScale{4.f};
    Character knight{win_size, win_size};

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{200.f, 600.f}, LoadTexture("nature_tileset/Log.png")}};

    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png"), &knight};
    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png"), &knight};

    Enemy *enemies[]{
        &goblin, &slime};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(WHITE);
        mapPos = Vector2Scale(knight.getWorldPos(), -1.);

        // draw map
        DrawTextureEx(worldMap, mapPos, 0., mapScale, WHITE);

        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive())
        {
            DrawRectangle(0., 0., win_size, win_size, Overlay);
            DrawText("Game Over!", 25, 100, 40, WHITE);
            EndDrawing();
            continue;
        }
        DrawRectangle(0, win_size, win_size, win_offset, WHITE);
        DrawText(TextFormat("Health: %.2f", knight.getHealth()), 10, win_size + 10, 20, BLACK);
        knight.tick(GetFrameTime());

        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + win_size > worldMap.width * mapScale ||
            knight.getWorldPos().y + win_size > worldMap.height * mapScale)
        {
            knight.undoMovement();
        }

        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollsionRec(knight.getWorldPos()), knight.getCollisionRec()))
                knight.undoMovement();
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                enemy->setAlive(!CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()));
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
