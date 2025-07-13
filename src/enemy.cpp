#include "includes/enemy.h"
#include "enemy.h"


Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex, Character* character)
{
    worldPos = pos;
    texture = idle_tex;
    idle = idle_tex;
    run = run_tex;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.5f;
    target = character;
    setAlive(false);
}

void Enemy::tick(float deltatime)
{
    if (!getAlive())
        return;
    // get target dimension
    velocity = target->getScreenPos() - getScreenPos();
    if (Vector2Length(velocity) < radius) velocity = {};
    BaseCharacter::tick(deltatime);

    if (CheckCollisionRecs(getCollisionRec(), target->getCollisionRec()))
        target->takeDamage(damagePerSec * deltatime);
}

Vector2 Enemy::getScreenPos()
{
    return worldPos - target->getWorldPos();
}
void Enemy::Reset(Vector2 spawnPos)
{
    worldPos = spawnPos;
    setAlive(false);
}