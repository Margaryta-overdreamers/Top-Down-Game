#ifndef CHARACTER_H
#define CHARACTER_H

#include "BaseCharacter.h"
#include "raylib.h"

class Character : public BaseCharacter 
{
public:
    Character(int winWidth, int winHeight);
    virtual Vector2 getScreenPos() override;
    virtual void Tick(float deltaTime) override;
    Rectangle getWeaponCollisionRec() const { return weaponCollissionRec; }
    void getDamage(float damage);
    float getHealth() const { return health; }
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon = LoadTexture("characters/weapon_sword.png");
    Rectangle weaponCollissionRec{};
    float health{100.f};
};

#endif