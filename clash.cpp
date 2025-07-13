#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "raymath.h"

#include "character.h"
#include "prop.h"
#include "enemyspawner.h"

Color Overlay = {0, 0, 0, 128};
const int win_size{384}, win_offset{32}, SPAWNDIST_MAX{2600}, MAX_PROPS{25};

typedef enum
{
    START,
    PLAYING,
    PAUSED,
    OVER
} State;

class Game
{
private:
    State state{START};
    Texture2D worldMap{LoadTexture("nature_tileset/WorldMap.png")};
    Vector2 mapPos{};
    const float mapScale{4.f};
    Character knight{win_size, win_size};
    Texture2D prop_textures[4]{
        LoadTexture("nature_tileset/Bush.png"),
        LoadTexture("nature_tileset/Log.png"),
        LoadTexture("nature_tileset/Rock.png"),
        LoadTexture("nature_tileset/Sign.png")};
    Prop props[MAX_PROPS];
    EnemySpawner spawner{
        &knight, LoadTexture("characters/goblin_idle_spritesheet.png"), 
        LoadTexture("characters/goblin_run_spritesheet.png"), 
        LoadTexture("characters/slime_idle_spritesheet.png"), 
        LoadTexture("characters/slime_run_spritesheet.png"), 20, 5};

    int score{};

public:
    Game()
    {
        for (int i = 0; i < MAX_PROPS; i++)
        {
            float rand_x = GetRandomValue(200, SPAWNDIST_MAX);
            float rand_y = GetRandomValue(200, SPAWNDIST_MAX);
            int type = GetRandomValue(0, 3);

            props[i] = Prop{Vector2{rand_x, rand_y}, prop_textures[type]};
        }
    }

    void Reset()
    {
        knight.Reset();
        spawner.Reset();
        state = PLAYING;
        score = 0;
    }

    Character getKnight() { return knight; }

    void DrawWorldMap()
    {
        mapPos = Vector2Scale(knight.getWorldPos(), -1.);
        DrawTextureEx(worldMap, mapPos, 0., mapScale, WHITE);

        for (auto prop : props)
            prop.Render(knight.getWorldPos());
    }

    void tick(float deltatime)
    {
        if (!knight.getAlive())
        {
            state = OVER;
            return;
        }
        else
        {
            if (IsKeyPressed(KEY_SPACE))
                state = state == PLAYING ? PAUSED : PLAYING;

            if (state == PLAYING)
            {
                knight.tick(deltatime);
                spawner.tick(deltatime);
                score = spawner.getScore();
                DrawRectangle(0, win_size, win_size, win_offset, WHITE);
                DrawText(TextFormat("Health: %.2f", knight.getHealth()), 10, win_size + 10, 20, BLACK);
                DrawText(TextFormat("Score: %i", score), 200, win_size + 10, 20, BLACK);

                // check map bounds
                if (knight.getWorldPos().x < 0.f ||
                    knight.getWorldPos().y < 0.f ||
                    knight.getWorldPos().x + win_size > worldMap.width * mapScale ||
                    knight.getWorldPos().y + win_size > worldMap.height * mapScale)
                {
                    knight.undoMovement();
                }

                for (auto prop : props)
                {
                    if (CheckCollisionRecs(prop.getCollsionRec(knight.getWorldPos()), knight.getCollisionRec()))
                        knight.undoMovement();
                }
            }
            else
            {
                DrawRectangle(0., 0., win_size, win_size + win_offset, Overlay);
                DrawText("Paused", 25, 100, 40, WHITE);
                DrawText("Press [Space] to play.", 25, 150, 20, WHITE);
            }
        }
    }

    State getState() { return state; }
    int getScore() {return score;}
};


int main()
{
    InitWindow(win_size, win_size + win_offset, "Classy Clash");
    Game game;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(WHITE);
        game.DrawWorldMap();

        if (game.getState() == OVER || game.getState() == START)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                game.Reset();
            }
            DrawRectangle(0., 0., win_size, win_size + win_offset, Overlay);
            const char *gameText = game.getState() == OVER ? "Game Over" : "Classy Clash!";
            DrawText(gameText, 25, 100, 40, WHITE);
            DrawText("Press [Enter] to play.", 25, 150, 20, WHITE);
            if (game.getState() == OVER)
                DrawText(TextFormat("Score: %i", game.getScore()), 25, 200, 20, WHITE);
            EndDrawing();
            continue;
        }
        game.tick(GetFrameTime());
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
