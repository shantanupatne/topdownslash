#include "character.h"

Character::Character(int win_w, int win_h)
{
    width = texture.width / maxFrames;
    height = texture.height;
    screenPos = {
        win_w / 2.f - scale * (0.5f * width),
        win_h / 2.f - scale * (0.5f * height),
    };
}

void Character::tick(float deltatime)
{
    worldPosLastFrame = worldPos;
    Vector2 direction{};
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        direction.x -= 1.;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        direction.x += 1.;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        direction.y += 1.;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        direction.y -= 1.;

    if (Vector2Length(direction) != 0.)
    {
        worldPos += Vector2Scale(Vector2Normalize(direction), speed);
        rightLeft = direction.x < 0.f ? -1.f : 1.f;
        texture = run;
    }
    else
        texture = idle;

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

void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle Character::getCollisionRec()
{
    return Rectangle{
        screenPos.x, screenPos.y, width * scale, height * scale};
}