#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter(){}

void BaseCharacter::Tick(float deltaTime)
{
    lastFramePos = worldPos;

    if (Vector2Length(velocity) != 0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        leftRight = velocity.x >= 0 ? 1.f : -1.f;
        texture = run;
    } 
    else
    {
        texture = idle;
    }
    velocity = {};

    // update animation
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame ++;
        runningTime = 0;
        if (frame > maxFrame)
        {
            frame = 0;
        }
    }

    // draw character
    Rectangle source{frame * width, 0.f, leftRight * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, width * scale, height * scale};
    DrawTexturePro(texture, source, dest, {}, 0.f, WHITE);
}

void BaseCharacter::undomovement()
{
    worldPos = lastFramePos;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{getScreenPos().x, getScreenPos().y, width * scale, height * scale};
}