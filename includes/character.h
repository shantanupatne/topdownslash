#pragma once
#include "includes/basecharacter.h"
class Character : public BaseCharacter
{
public:
    Character(int win_w, int win_h);
    virtual void tick(float deltatime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() {return weaponCollisionRec;}
    float getHealth() const { return health; }
    void takeDamage(float damage);
    virtual void Reset() override;
private:
    int win_w{}, win_h{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health {100.f};
};

