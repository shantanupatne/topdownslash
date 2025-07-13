#pragma once
#include <memory>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "enemy.h"

typedef enum
{
    GOBLIN,
    SLIME
} EnemyType;

class EnemySpawner
{
private:
    int maxEnemies{5}, activeCount{};
    float runningTime{}, spawnTime{1.};
    Texture2D idle, run, goblinIdle, goblinRun, slimeIdle, slimeRun;
    EnemyType type;
    std::vector<std::unique_ptr<Enemy>> enemyPool;
    Character *target;
    Vector2 GetRandomSpawnPosition()
    {
        Vector2 pos;
        do
        {
            pos = {static_cast<float>(GetRandomValue(200, 2600)),
                   static_cast<float>(GetRandomValue(200, 2600))};
        } while (Vector2Distance(pos, target->getWorldPos()) < 200.f);
        return pos;
    }
    int score{};

public:
    EnemySpawner(Character* player, Texture2D gIdle, Texture2D gRun, Texture2D sIdle, Texture2D sRun, int poolSize, int maxActive);
    void spawnEnemy();
    void tick(float deltatime);
    void Reset();
    int getScore() {return score;}
    std::vector<std::unique_ptr<Enemy>> &getEnemies() { return enemyPool; }
};