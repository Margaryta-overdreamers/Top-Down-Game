#include "prop.h"
#include "raymath.h"

Prop::Prop(Texture2D tex, Vector2 pos)
{
    texture = tex;
    worldPos = pos;
}

void Prop::Render(Vector2 knightPos)
{
    Vector2 screenPos = Vector2Subtract(worldPos, knightPos);
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 knightPos)
{
    Vector2 screenPos = Vector2Subtract(worldPos, knightPos);
    return Rectangle{ 
        screenPos.x + 20.f, screenPos.y + 10.f, 
        (texture.width * scale) * 0.7f, (texture.height * scale) * 0.7f
    };
}