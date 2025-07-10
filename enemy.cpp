#include "enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex)
{
    worldPos = pos;
    texture = idle_tex;
    idle = idle_tex;
    run = run_tex;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.5f;
}

void Enemy::tick(float deltatime)
{
    if (!getAlive()) return;
    // get target dimension
    velocity = target->getScreenPos() - getScreenPos();
    BaseCharacter::tick(deltatime);
}

Vector2 Enemy::getScreenPos()
{
    return worldPos - target->getWorldPos();
}