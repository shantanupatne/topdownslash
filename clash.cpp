#include <iostream>
#ifndef RAYMATH
#include "raylib.h"
#include "raymath.h"
#define RAYMATH
#endif

#include "character.h"

int main()
{
    const int win_size{384};

    InitWindow(win_size, win_size, "Classy Clash");
    Texture2D worldMap = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0., 0.};
    float mapScale{4.f};
    Character knight{win_size, win_size};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(WHITE);
        mapPos = Vector2Scale(knight.getWorldPos(), -1.);
        // draw map
        DrawTextureEx(worldMap, mapPos, 0., mapScale, WHITE);

        knight.tick(GetFrameTime());

        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + win_size > worldMap.width * mapScale ||
            knight.getWorldPos().y + win_size > worldMap.height * mapScale)
        {
            knight.undoMovement();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
