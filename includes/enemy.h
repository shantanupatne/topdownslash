#pragma once
#include "includes/basecharacter.h"
#include "includes/character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex, Character* character);
    virtual void tick(float deltatime) override;
    virtual Vector2 getScreenPos() override;
    virtual void Reset() override;
private:
    Character* target;  
    float damagePerSec{10.f}, radius{0.5f};
};