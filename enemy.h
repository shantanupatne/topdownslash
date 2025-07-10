#ifndef RAYMATH
#define RAYMATH
#include "raylib.h"
#include "raymath.h"
#endif

#include "basecharacter.h"
#include "character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex);
    virtual void tick(float deltatime) override;
    void setTarget(Character* character) { target = character; }

private:
    Character* target;  

};