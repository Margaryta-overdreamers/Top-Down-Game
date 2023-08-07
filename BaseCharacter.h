#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    virtual Vector2 getScreenPos() = 0;
    Vector2 getWorldPos() const { return worldPos; }
    virtual void Tick(float deltaTime);
    void undomovement();
    Rectangle getCollisionRec(); 
    bool getAlive() const { return Alive; }
    void setAlive(bool isAlive) { Alive = isAlive; }
protected:
    Texture2D texture{};
    Texture2D idle{};
    Texture2D run{};
    Vector2 worldPos{};
    Vector2 velocity{};
    Vector2 lastFramePos{};
    float scale{4.f};
    float speed{4.f};
    int maxFrame{6};
    float width{};
    float height{};
    float runningTime{};
    float updateTime{1.f/12.f};
    int frame{};
    float leftRight{1.f};
private:
    bool Alive{true};
};

#endif 