#include "enemy.h"
#include "raymath.h"

Enemy::Enemy(Texture2D idle_tex, Texture2D run_tex, Vector2 pos)
{
    texture = idle_tex;
    idle = idle_tex;
    run = run_tex;
    worldPos = pos;
    speed = 2.75f;

    width = texture.width / maxFrame;
    height = texture.height;
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}

void Enemy::Tick(float deltaTime)
{
    if(!getAlive()) return;

    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < radius)
    {
        velocity = {};
    }

    BaseCharacter::Tick(deltaTime);

    if(CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->getDamage(damagePerSec * deltaTime);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            setAlive(false);
        }
    }
}