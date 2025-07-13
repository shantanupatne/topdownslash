#include "enemyspawner.h"

EnemySpawner::EnemySpawner(Character* player, Texture2D gIdle,
                           Texture2D gRun, Texture2D sIdle,
                           Texture2D sRun, int poolSize, int maxActive) : maxEnemies(maxActive), goblinIdle(gIdle),
                                                                          goblinRun(gRun), slimeIdle(sIdle),
                                                                          slimeRun(sRun), target(player)
{
    for (int i = 0; i < poolSize; ++i)
    {
        Vector2 pos = GetRandomSpawnPosition();
        Texture2D idle = (i % 2 == 0) ? goblinIdle : slimeIdle;
        Texture2D run = (i % 2 == 0) ? goblinRun : slimeRun;

        enemyPool.push_back(std::make_unique<Enemy>(pos, idle, run, target));
    }
    activeCount = 0;
};

void EnemySpawner::spawnEnemy()
{
    for (auto &enemy : enemyPool)
    {
        if (activeCount >= maxEnemies) break;
        if (!enemy->getAlive())
        {
            enemy->Reset(GetRandomSpawnPosition());
            enemy->setAlive(true);
            activeCount++;
        }
    }
}

void EnemySpawner::tick(float deltatime)
{
    runningTime += deltatime;
    if (runningTime >= spawnTime)
    {
        spawnEnemy();
        runningTime = 0;
    }

    for (auto &enemy : enemyPool)
    {
        if (enemy->getAlive())
        {
            enemy->tick(deltatime);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), target->getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                    activeCount--;
                    score += 10;
                }
            }
        }
    }
};

void EnemySpawner::Reset()
{
    for (auto &enemy : enemyPool)
    {
        enemy->Reset(GetRandomSpawnPosition());
    }
    activeCount = 0;
    score = 0;
};