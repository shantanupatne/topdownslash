#pragma once
#include "raylib.h"
#include "raymath.h"


class BaseCharacter
{
public:
    BaseCharacter();
    void undoMovement();
    Rectangle getCollisionRec();
    Vector2 getWorldPos() { return worldPos; }
    virtual Vector2 getScreenPos() = 0;
    virtual void tick(float deltatime);
    bool getAlive() {return alive;}
    void setAlive(bool isAlive) {alive = isAlive;}

protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};

    Vector2 worldPos{}, worldPosLastFrame{}, velocity{};

    float rightLeft{1.f}, runningTime{}, height{}, width{}, updateTime{1.f / 12.f}, speed{4.f}, scale{4.f};
    int frame{}, maxFrames{6}, SPAWNDIST_MAX{2600}; 

private:
    bool alive{true};  
};

