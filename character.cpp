#include "character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    texture = LoadTexture("characters/knight_idle_spritesheet.png");
    idle = LoadTexture("characters/knight_idle_spritesheet.png");
    run = LoadTexture("characters/knight_run_spritesheet.png");
    windowWidth = winWidth;
    windowHeight = winHeight;

    width = texture.width / maxFrame;
    height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2 {
        static_cast<float>(windowWidth)/2.f - scale * (0.5f * width),
        static_cast<float>(windowHeight)/2.f - scale * (0.5f * height)
    };   
}

void Character::Tick(float deltaTime)
{
    if(!getAlive()) return;
    
    if (IsKeyDown(KEY_LEFT)) velocity.x -= 1.f;
    if (IsKeyDown(KEY_RIGHT)) velocity.x += 1.f;
    if (IsKeyDown(KEY_UP)) velocity.y -= 1.f;
    if (IsKeyDown(KEY_DOWN)) velocity.y += 1.f;

    BaseCharacter::Tick(deltaTime);

    Vector2 offset{};
    Vector2 origin{};
    float rotation{};

    if (leftRight > 0)
    {
        offset = {35.f, (weapon.height * scale) -10.f};
        origin = {0.f, weapon.height * scale};
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 25.f : 0.f;
        weaponCollissionRec = {
            getScreenPos().x + offset.x - origin.x, 
            getScreenPos().y + offset.y - origin.y, 
            weapon.width * scale, weapon.height *scale
        };
    }
    else
    {
        offset = {25.f, (weapon.height * scale) - 10.f};
        origin = {weapon.width * scale, weapon.height * scale};
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -25.f : 0.f;
        weaponCollissionRec = {
            getScreenPos().x + offset.x - origin.x, 
            getScreenPos().y + offset.y - origin.y, 
            weapon.width * scale, weapon.height *scale
        };
    }

    Rectangle weaponSource{ 0.f, 0.f, leftRight * static_cast<float>(weapon.width), static_cast<float>(weapon.height)};
    Rectangle weaponDest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, weaponSource, weaponDest, origin, rotation, WHITE);
}

void Character::getDamage(float damage)
{
    health -= damage;
    if (health <= 0)
    {
        setAlive(false);
    }
}