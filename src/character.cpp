#include "includes/character.h"
#include "character.h"

Character::Character(int win_w, int win_h): win_w(win_w), win_h(win_h)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos() {
    return Vector2 {
        win_w / 2.f - scale * (0.5f * width),
        win_h / 2.f - scale * (0.5f * height),
    };

}

void Character::tick(float deltatime)
{

    if (!getAlive()) return;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        velocity.x -= 1.;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        velocity.x += 1.;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        velocity.y += 1.;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        velocity.y -= 1.;

    BaseCharacter::tick(deltatime);

    
    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightLeft > 0.f) {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - (weapon.height * scale),
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 35.f : 0.f;
    } else {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - (weapon.width * scale),
            getScreenPos().y + offset.y - (weapon.height * scale),
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -35.f : 0.f;
    }
    // draw sword
    Rectangle source{0.f, 0.f, weapon.width * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
}

void Character::takeDamage(float damage) {
    health -= damage;
    if (health <= 0.f) setAlive(false);
}
void Character::Reset()
{
    health = 100;
    worldPos = {0, 0};
    setAlive(true);
}