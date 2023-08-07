#include "BaseCharacter.h"
#include "character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Texture2D idle_tex, Texture2D run_tex, Vector2 pos);
    virtual Vector2 getScreenPos() override;
    virtual void Tick(float deltaTime) override;
    void getTarget(Character* character) { target = character; } 
private:
    Character* target;
    float radius{25.f};
    float damagePerSec{10.f};
};