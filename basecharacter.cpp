#include "basecharacter.h"

BaseCharacter::BaseCharacter(){}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        screenPos.x, screenPos.y, width * scale, height * scale};
}

void BaseCharacter::tick(float deltatime)
{
    worldPosLastFrame = worldPos;

    // update animation
    runningTime += deltatime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        frame = frame % maxFrames;
    }

    Rectangle source{frame * width, 0.f, rightLeft * width, height};         // sprite from texture
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height}; // location on the map
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}