#ifndef RAYMATH
#define RAYMATH
#include "raylib.h"
#include "raymath.h"
#endif

#ifndef CHARACTER_H
#define CHARACTER_H
#include "basecharacter.h"
class Character : public BaseCharacter
{
public:
    Character(int win_w, int win_h);
    virtual void tick(float deltatime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() {return weaponCollisionRec;}
private:
    int win_w{}, win_h{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
};

#endif