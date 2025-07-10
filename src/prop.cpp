#include "includes/prop.h"

Prop::Prop(Vector2 pos, Texture2D tex) : worldPos(pos), texture(tex)
{
}

void Prop::Render(Vector2 knightPos)
{
    Vector2 screenPos{worldPos - knightPos};
    DrawTextureEx(texture, screenPos, 0., scale, WHITE);
}

Rectangle Prop::getCollsionRec(Vector2 knightPos)
{
    Vector2 screenPos{worldPos - knightPos};
    return Rectangle
    {
        screenPos.x, screenPos.y, scale *texture.width, scale *texture.height
    };
}