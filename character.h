#ifndef RAYMATH
#include "raylib.h"
#include "raymath.h"
#define RAYMATH
#endif

class Character
{
private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};

    Vector2 screenPos{}, worldPos{}, worldPosLastFrame{};

    float rightLeft{1.f}, runningTime{}, height{}, width{}, updateTime{1.f / 12.f}, speed{4.f}, scale{4.f};
    int frame{}, maxFrames{6};    

public:
    Character(int win_w, int win_h);
    Vector2 getWorldPos() { return worldPos; }
    void tick(float deltatime);
    void undoMovement();
};