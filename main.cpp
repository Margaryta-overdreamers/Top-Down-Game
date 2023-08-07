#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "enemy.h"
#include <string>

int main()
{
    const int windowWidth{385};
    const int windowHeight{385};
    InitWindow(windowWidth, windowHeight, "Top Down Game");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{};
    float scale{4.f};

    Prop props[5]{
        {LoadTexture("nature_tileset/Bush.png"), {400,400}},
        {LoadTexture("nature_tileset/Log.png"), {800,200}},
        {LoadTexture("nature_tileset/Rock.png"), {1200,1700}},
        {LoadTexture("nature_tileset/Sign.png"), {770,350}},
        {LoadTexture("nature_tileset/Bush.png"), {300,900}}
    };

    Character knight(windowWidth, windowHeight);
    
    Enemy goblin(
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png"),
        {600, 100}
    );
    Enemy slime(
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png"),
        {800, 800}
    );

    Enemy* enemies[]{
        &goblin, &slime
    };

    for (auto enemy:enemies)
    {
        enemy->getTarget(&knight);
    }

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        DrawTextureEx(map, mapPos, 0.f, scale, WHITE);

        for (auto prop:props)
        {
            prop.Render(knight.getWorldPos());
        }

        knight.Tick(GetFrameTime());
        
        for (auto enemy:enemies)
        {
            enemy->Tick(GetFrameTime());
        }

        if(!knight.getAlive())
        {
            DrawText("GAME OVER", 45.f, 55.f, 50, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 45.f, 55.f, 40, RED);
        }

        if (knight.getWorldPos().x < 0 || knight.getWorldPos().y < 0 ||
            knight.getWorldPos().x + windowWidth >= map.width * scale ||
            knight.getWorldPos().y + windowHeight >= map.height * scale)
        {
            knight.undomovement();
        }

        for (auto prop:props)
        {
            if (CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getWorldPos())))
            {
                knight.undomovement();
            }
        }


        EndDrawing();
    }
    CloseWindow();
}