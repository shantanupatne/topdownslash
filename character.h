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

private:
};

#endif