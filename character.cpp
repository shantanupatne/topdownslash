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
    BaseCharacter::tick(deltatime);
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

}

