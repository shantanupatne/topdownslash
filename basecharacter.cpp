#include "basecharacter.h"

BaseCharacter::BaseCharacter() {}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x, getScreenPos().y, width * scale, height * scale};
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

    if (Vector2Length(velocity) != 0.)
    {
        worldPos += Vector2Scale(Vector2Normalize(velocity), speed);
        rightLeft = velocity.x < 0.f ? -1.f : 1.f;
        texture = run;
    }
    else
        texture = idle;

    velocity = {};
    Rectangle source{frame * width, 0.f, rightLeft * width, height};                   // sprite from texture
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height}; // location on the map
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}