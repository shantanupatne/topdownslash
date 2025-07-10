#ifndef RAYMATH
#include "raylib.h"
#include "raymath.h"
#define RAYMATH
#endif

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 knightPos);
    Rectangle getCollsionRec(Vector2 knightPos);
private:
    Vector2 worldPos;
    Texture2D texture;
    float scale{4.f};
};